/***************************************************************************/ /**
 * @file app.h
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SOCKET_SERVER_APP_H
#define SOCKET_SERVER_APP_H

/***************************************************************************/ /**
 * Initialize application.
 ******************************************************************************/
void socket_server_init(void* args);

/***************************************************************************/ /**
 * App ticking function.
 ******************************************************************************/
void socket_server_task(void* args);

#endif // SOCKET_SERVER_H
