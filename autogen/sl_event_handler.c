#include "sl_event_handler.h"

#include "rsi_chip.h"
#include "rsi_nvic_priorities_config.h"
#include "sli_siwx917_soc.h"
#include "rsi_board.h"
#include "rsi_debug.h"
#include "cmsis_os2.h"
#define INTF_PLL_CLK      (160000000)
#define INTF_PLL_REF_CLK  (80000000)

void up_cpu_clk() {
  int32_t status = 0;
  /* program intf pll to 180Mhz */
  status = RSI_CLK_SetIntfPllFreq(M4CLK, INTF_PLL_CLK, INTF_PLL_REF_CLK);
  if (status != RSI_OK) {
   // printf("Failed to Configure Interface PLL Clock, Error Code : %d.\n", status);
    return;
  } else {
    //printf("Configured Interface PLL Clock to 180Mhz.\n");
  }

  /* Configure m4 soc to 180Mhz */
  status = RSI_CLK_M4SocClkConfig(M4CLK, M4_INTFPLLCLK, 0);
  if (status != RSI_OK) {
    //printf("Failed to Set M4 Clock as Interface PLL clock,Error Code : %d.\n", status);
    return;
  } else {
      //printf("Set M4 Clock as Interface PLL clock.\n");
  }
}
void sl_platform_init(void)
{
  SystemCoreClockUpdate();
  up_cpu_clk();
  sl_si91x_device_init_nvic();
  sli_si91x_platform_init();
  RSI_Board_Init();
  DEBUGINIT();
  osKernelInitialize();
}

void sl_kernel_start(void)
{
  osKernelStart();
}

void sl_driver_init(void)
{
}

void sl_service_init(void)
{
}

void sl_stack_init(void)
{
}

void sl_internal_app_init(void)
{
}

