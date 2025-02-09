/***************************************************************************/ /**
 * @file
 * @brief  Twt Use Case Remote App
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include <string.h>
#include <stdint.h>
#include "errno.h"
#include "sl_wifi_callback_framework.h"
#include "sl_status.h"
#include "sl_board_configuration.h"
#include "cmsis_os2.h"
#include "string.h"
#include "sl_wifi.h"
#include "socket.h"
#include "sl_utility.h"
#include "sl_net.h"
#include "sl_ip_types.h"
#include "sl_string.h"
#include "sl_net_si91x.h"
#include "sl_net_wifi_types.h"
#include "sl_si91x_socket_utility.h"
#include "sl_si91x_socket_constants.h"
#include "sl_si91x_socket.h"
#include <socket_server_app.h>

#ifdef SLI_SI91X_MCU_INTERFACE
#include "rsi_power_save.h"
#include "rsi_wisemcu_hardware_setup.h"
#endif
/******************************************************
 *                      Macros
 ******************************************************/
#define NET_USE_STA 0

/** debug usage **/
#define ON_SOCKET_APP_START 0
#define ON_SOCKET_DATA_RECEIVE 1
#define GSPI_RELEASE ON_SOCKET_APP_START

/******************************************************
 *                    Constants
 ******************************************************/
#define TCP_RECEIVE        1
#define BACK_LOG           1
#define TCP_LISTENING_PORT 5001
#define UDP_LISTENING_PORT 5002
#define AP_VAP 1

#if TCP_RECEIVE
#define EXPECTED_DATA_SIZE (sizeof("Door lock opened") - 1)
#else
#define EXPECTED_DATA_SIZE 1470
#endif
#define RSI_MAX_TCP_RETRIES  10
#define RECEIVE_DATA_TIMEOUT 2000 // command interval in milli seconds

sl_mac_address_t ampak_mac = {{0x94, 0xB2, 0x16, 0x98, 0xD4, 0x2A}};

static const sl_wifi_device_configuration_t sl_wifi_twt_concurrent_configuration = {
  .boot_option = LOAD_NWP_FW,
  .mac_address = &ampak_mac,
  .band        = SL_SI91X_WIFI_BAND_2_4GHZ,
  .boot_config = { .oper_mode = SL_SI91X_CONCURRENT_MODE,
                   .coex_mode = SL_SI91X_WLAN_ONLY_MODE,
                   .feature_bit_map =
                     (SL_SI91X_FEAT_SECURITY_OPEN | SL_SI91X_FEAT_AGGREGATION | SL_SI91X_FEAT_ULP_GPIO_BASED_HANDSHAKE
#ifdef SLI_SI91X_MCU_INTERFACE
                      | SL_SI91X_FEAT_WPS_DISABLE
#endif
                      ),
                   .tcp_ip_feature_bit_map     = (SL_SI91X_TCP_IP_FEAT_DHCPV4_SERVER | SL_SI91X_TCP_IP_FEAT_DHCPV4_CLIENT | SL_SI91X_TCP_IP_FEAT_DNS_CLIENT
                                              | SL_SI91X_TCP_IP_FEAT_EXTENSION_VALID),
                   .custom_feature_bit_map     = (SL_SI91X_CUSTOM_FEAT_EXTENTION_VALID),
                   .ext_custom_feature_bit_map = (SL_SI91X_EXT_FEAT_LOW_POWER_MODE | SL_SI91X_EXT_FEAT_XTAL_CLK
                                                  | SL_SI91X_EXT_FEAT_DISABLE_DEBUG_PRINTS | MEMORY_CONFIG
#ifdef SLI_SI917
                                                  | SL_SI91X_EXT_FEAT_FRONT_END_SWITCH_PINS_ULP_GPIO_4_5_0
#endif
                                                  ),
                   .bt_feature_bit_map         = 0,
                   .ext_tcp_ip_feature_bit_map = SL_SI91X_CONFIG_FEAT_EXTENTION_VALID,
                   .ble_feature_bit_map        = 0,
                   .ble_ext_feature_bit_map    = 0,
                   .config_feature_bit_map     = SL_SI91X_FEAT_SLEEP_GPIO_SEL_BITMAP }
};

/******************************************************
 *               Variable Definitions
 ******************************************************/
extern osSemaphoreId_t gspi_thread_sem;

const osThreadAttr_t socket_server_thread_attributes = {
  .name       = "socket_server_thread",
  .attr_bits  = 0,
  .cb_mem     = 0,
  .cb_size    = 0,
  .stack_mem  = 0,
  .stack_size = 3072,
  .priority   = osPriorityNone,
  .tz_module  = 0,
  .reserved   = 0,
};

sl_ip_address_t ip_address           = { 0 };

#if NET_USE_STA
sl_net_wifi_client_profile_t client_profile = { 0 };
#else
sl_net_wifi_ap_profile_t ap_profile = { 0 };
#endif

int tcp_server_socket = -1, tcp_client_socket = -1, udp_server_socket = -1;
int server_socket;

uint32_t start_rx = 0, start_rtt = 0, end_rtt = 0;
volatile uint32_t num_pkts = 0;

volatile uint8_t data_sent                 = 0;
volatile uint8_t data_recvd                = 0;
volatile uint64_t num_bytes                = 0;
volatile int8_t rxBuff[EXPECTED_DATA_SIZE] = { 0 };
uint32_t reconnect = 0;

/******************************************************
  *               Function Declarations
  ******************************************************/
void socket_server_task();
sl_status_t create_tcp_server(void);
sl_status_t create_udp_server(void);
sl_status_t send_and_receive_data(void);

/******************************************************
  *               Function Definitions
  ******************************************************/
void data_callback(uint32_t sock_no, uint8_t *buffer, uint32_t length)
{
  UNUSED_PARAMETER(sock_no);
  uint16_t i = 0;
  num_bytes += length;
  num_pkts++;
  memcpy((void *)rxBuff, buffer, length);
  printf("Received %ld bytes\r\n", length);
  printf("\"");
#if GSPI_RELEASE == ON_SOCKET_DATA_RECEIVE
  osSemaphoreRelease(gspi_thread_sem);
#endif

  for (i = 0; i < length; i++) {
    printf("%c", buffer[i]);
  }
  printf("\"");
  if (data_recvd == 0) {
    end_rtt = osKernelGetTickCount();
    printf("\r\nOverall RTT : 0x%lX\r\n", (end_rtt - start_rtt));
    data_recvd = 1;
  }
}

void socket_server_init(void* args)
{
  UNUSED_PARAMETER(args);
  osThreadNew((osThreadFunc_t)socket_server_task, args, &socket_server_thread_attributes);
}

void socket_server_task(void* args)
{
  UNUSED_PARAMETER(args);

#if GSPI_RELEASE == ON_SOCKET_APP_START
  osSemaphoreRelease(gspi_thread_sem);
#endif
  sl_status_t status;
  printf("\r\n");
  printf("Set user-def MAC: %x:%x:%x:%x:%x:%x \r\n"
        ,sl_wifi_twt_concurrent_configuration.mac_address->octet[0]
        ,sl_wifi_twt_concurrent_configuration.mac_address->octet[1]
        ,sl_wifi_twt_concurrent_configuration.mac_address->octet[2]
        ,sl_wifi_twt_concurrent_configuration.mac_address->octet[3]
        ,sl_wifi_twt_concurrent_configuration.mac_address->octet[4]
        ,sl_wifi_twt_concurrent_configuration.mac_address->octet[5]);

#if NET_USE_STA
  status = sl_net_init(SL_NET_WIFI_CLIENT_INTERFACE, &sl_wifi_twt_concurrent_configuration, NULL, NULL);
  if (status != SL_STATUS_OK) {
    printf("Failed to start Wi-Fi client interface: 0x%lx\r\n", status);
    return;
  }
  printf("Wi-Fi Init Done\r\n");

  status = sl_net_up(SL_NET_WIFI_CLIENT_INTERFACE, 0);
  if (status != SL_STATUS_OK) {
    printf("Failed to bring Wi-Fi client interface up: 0x%lx\r\n", status);
    return;
  }
  printf("Wi-Fi client up\r\n");

  status = sl_net_get_profile(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID, &client_profile);
  if (status != SL_STATUS_OK) {
    printf("Failed to get client profile: 0x%lx\r\n", status);
    return;
  }
  printf("Success to get client profile\r\n");

  ip_address.type = SL_IPV4;
  memcpy(&ip_address.ip.v4.bytes, &client_profile.ip.ip.v4.ip_address.bytes, sizeof(sl_ipv4_address_t));
  print_sl_ip_address(&ip_address);
  printf("\r\n");

  sl_mac_address_t get_mac;
  status = sl_wifi_get_mac_address(SL_WIFI_CLIENT_INTERFACE, &get_mac);
  if (status != SL_STATUS_OK) {
      printf("Failed to get ap MAC: 0x%lx\r\n", status);
      return;
    }
  printf("Get user-def MAC: %x:%x:%x:%x:%x:%x \r\n"
      ,get_mac.octet[0]
      ,get_mac.octet[1]
      ,get_mac.octet[2]
      ,get_mac.octet[3]
      ,get_mac.octet[4]
      ,get_mac.octet[5]);
#else
  status = sl_net_init(SL_NET_WIFI_AP_INTERFACE, &sl_wifi_twt_concurrent_configuration, NULL, NULL);
  if (status != SL_STATUS_OK) {
    printf("Failed to start Wi-Fi ap interface: 0x%lx\r\n", status);
    return;
  }
  printf("Wi-Fi Init Done\r\n");

  status = sl_net_up(SL_NET_WIFI_AP_INTERFACE, 0);
  if (status != SL_STATUS_OK) {
    printf("Failed to bring Wi-Fi ap interface up: 0x%lx\r\n", status);
    return;
  }
  printf("Wi-Fi ap up\r\n");

  status = sl_net_get_profile(SL_NET_WIFI_AP_INTERFACE, SL_NET_DEFAULT_WIFI_AP_PROFILE_ID, &ap_profile);
  if (status != SL_STATUS_OK) {
    printf("Failed to get ap profile: 0x%lx\r\n", status);
    return;
  }
  printf("Success to get ap profile\r\n");

  ip_address.type = SL_IPV4;
  memcpy(&ip_address.ip.v4.bytes, &ap_profile.ip.ip.v4.ip_address.bytes, sizeof(sl_ipv4_address_t));
  print_sl_ip_address(&ip_address);
  printf("\r\n");
  sl_mac_address_t get_mac;
  status = sl_wifi_get_mac_address(SL_WIFI_AP_INTERFACE, &get_mac);
  if (status != SL_STATUS_OK) {
      printf("Failed to get ap MAC: 0x%lx\r\n", status);
      return;
    }
  printf("Get user-def MAC: %x:%x:%x:%x:%x:%x \r\n"
      ,get_mac.octet[0]
      ,get_mac.octet[1]
      ,get_mac.octet[2]
      ,get_mac.octet[3]
      ,get_mac.octet[4]
      ,get_mac.octet[5]);
#endif


Loop:
  status = create_tcp_server();
  if (status != SL_STATUS_OK) {
    printf("Error while creating TCP server: 0x%lx \r\n", status);
    return;
  }
  printf("TCP Server is running\r\n");

#if !TCP_RECEIVE
  status = create_udp_server();
  if (status != SL_STATUS_OK) {
    printf("Error while creating UDP server: 0x%lx \r\n", status);
    return;
  }
  printf("UDP Server is running\r\n");
#endif

  status = send_and_receive_data();
  if (status != SL_STATUS_OK) {
    printf("Send and Receive Data fail: 0x%lx \r\n", status);
    //return;
  }

goto Loop;
}

sl_status_t create_tcp_server(void)
{
  uint8_t max_tcp_retry             = RSI_MAX_TCP_RETRIES;
  struct sockaddr_in server_address = { 0 };

  int socket_return_value = 0;

#if !NET_USE_STA
  uint8_t ap_vap = AP_VAP;
#endif

  if(reconnect == 0)
  {
    tcp_server_socket = sl_si91x_socket_async(AF_INET, SOCK_STREAM, IPPROTO_TCP, &data_callback);
    if (tcp_server_socket < 0) {
      printf("TCP Socket creation failed with BSD error: %d\r\n", errno);
      return SL_STATUS_FAIL;
    }
    printf("\r\nTCP Server Socket ID : %d\r\n", tcp_server_socket);
#if NET_USE_STA
    socket_return_value = sl_si91x_setsockopt_async(tcp_server_socket,
                                                    SOL_SOCKET,
                                                    SL_SI91X_SO_MAXRETRY,
                                                    &max_tcp_retry,
                                                    sizeof(max_tcp_retry));
#else
    socket_return_value = sl_si91x_setsockopt_async(server_socket,
                                                    SOL_SOCKET,
                                                    SL_SI91X_SO_SOCK_VAP_ID,
                                                    &ap_vap,
                                                    sizeof(ap_vap));
#endif

    if (socket_return_value < 0) {
      printf("TCP Set Socket option failed with BSD error: %d\r\n", errno);
      close(tcp_server_socket);
      return SL_STATUS_FAIL;
    }
    printf("TCP Set Sock Option: Max retry set : %d\r\n", max_tcp_retry);

    server_address.sin_family = AF_INET;
    server_address.sin_port   = TCP_LISTENING_PORT;

    socket_return_value =
        sl_si91x_bind(tcp_server_socket, (struct sockaddr *)&server_address, sizeof(struct sockaddr_in));
    if (socket_return_value < 0) {
      printf("TCP Socket bind failed with BSD error: %d\r\n", errno);
      close(tcp_server_socket);
      return SL_STATUS_FAIL;
    }
    printf("TCP Bind Success\r\n");

    socket_return_value = sl_si91x_listen(tcp_server_socket, BACK_LOG);
    if (socket_return_value < 0) {
      printf("TCP Socket listen failed with BSD error: %d\r\n", errno);
      close(tcp_server_socket);

      //VERIFY_STATUS_AND_RETURN(socket_return_value);
      return SL_STATUS_FAIL;
    }
    printf("TCP Listening on Local Port : %d\r\n", TCP_LISTENING_PORT);
  }
  if(1 /*(reconnect == 1) || (reconnect == 0)*/)
  {
    tcp_client_socket = sl_si91x_accept(tcp_server_socket, NULL, 0);
    if (tcp_client_socket < 0) {
      printf("Socket accept failed with BSD error: %d\r\n", errno);
      close(tcp_server_socket);
      return SL_STATUS_FAIL;
    }
    printf("TCP Socket Accept Success\r\n");
    return SL_STATUS_OK;
  }
  printf("TCP Client Socket ID : %d\r\n", tcp_client_socket);
  return SL_STATUS_OK;
}

sl_status_t create_udp_server(void)
{
  struct sockaddr_in server_address = { 0 };
  int socket_return_value           = 0;

  udp_server_socket = sl_si91x_socket_async(AF_INET, SOCK_DGRAM, IPPROTO_UDP, &data_callback);
  if (udp_server_socket < 0) {
    printf("UDP Socket creation failed with BSD error: %d\r\n", errno);
    return SL_STATUS_FAIL;
  }
  printf("UDP Server Socket ID : %d\r\n", udp_server_socket);

  server_address.sin_family = AF_INET;
  server_address.sin_port   = UDP_LISTENING_PORT;

  socket_return_value =
      sl_si91x_bind(udp_server_socket, (struct sockaddr *)&server_address, sizeof(struct sockaddr_in));
  if (socket_return_value < 0) {
    printf("UDP Socket bind failed with BSD error: %d\r\n", errno);
    close(udp_server_socket);
    return SL_STATUS_FAIL;
  }
  printf("UDP Bind Success\r\n");

  return SL_STATUS_OK;
}

sl_status_t send_and_receive_data(void)
{
  int status = SL_STATUS_OK;
  while (1) {
    if (data_sent == 0) {
      start_rtt  = osKernelGetTickCount();
      data_sent  = 1;
      data_recvd = 0;
      status     = sl_si91x_send(tcp_client_socket, (uint8_t *)"Stream Data", (sizeof("Stream Data") - 1), 0);
      printf("\r\nSending Command\r\n");
      if (status < 0) {
        data_sent = 0;
        sl_si91x_shutdown(tcp_client_socket, SHUTDOWN_BY_ID);
        printf("\r\nFailed to Send data to TCP Server, Error Code : 0x%x\r\n", status);
        reconnect = 1;
        return SL_STATUS_FAIL;
      }
    }

    printf("Command Sent. Listening for data\r\n");
    start_rx = osKernelGetTickCount();
    printf("Start time TX: 0x%lX\r\n", start_rx);

    do {
      osThreadYield();
    } while (((osKernelGetTickCount() - start_rx) < RECEIVE_DATA_TIMEOUT));

    start_rtt = 0;
    printf("Number of packets received : 0x%lX\n", num_pkts);
    printf("Number of bytes received : 0x%lx\n", (long)num_bytes);
    num_bytes = 0;
    num_pkts  = 0;
    printf("Data Reception Completed\r\n");
    data_sent = 0;
  }
  return SL_STATUS_OK;
}
