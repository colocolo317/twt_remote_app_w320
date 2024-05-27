/*
 * gspi_util.h
 *
 *  Created on: 2024/5/8
 *      Author: ch.wang
 */

#ifndef GSPI_UTIL_H_
#define GSPI_UTIL_H_

#define SL_USE_TRANSFER ENABLE
#define SL_USE_SEND     DISABLE
#define SL_USE_RECEIVE  DISABLE

// -----------------------------------------------------------------------------
// Prototypes
/***************************************************************************/ /**
 * GSPI initialization function
 * Clock is configured, followed by power mode, and GSPI configuration
 *
 * @param none
 * @return none
 ******************************************************************************/
void gspi_init(void);

void gspi_task(void* arguments);

#endif /* GSPI_UTIL_H_ */
