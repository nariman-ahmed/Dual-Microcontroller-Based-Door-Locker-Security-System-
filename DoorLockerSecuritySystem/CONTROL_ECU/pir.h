/*
 * pir.h
 *
 *  Created on: 2 Nov 2024
 *      Author: NARIMAN AHMED
 */

#ifndef PIR_H_
#define PIR_H_

#include "std_types.h"

#define PIR_PORT    PORTC_ID
#define PIR_PIN     PIN2_ID

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

void PIR_init(void);
uint8 PIR_getState(void);

#endif /* PIR_H_ */
