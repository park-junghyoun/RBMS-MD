#ifndef BMS_USER_FIRMWARE_EXAMPLE_H
#define BMS_USER_FIRMWARE_EXAMPLE_H

#include "r_bms_api.h"
#include "iodefine.h"

#define LED7			P0.0				//LED 1 Pin
#define LED6			P0.1				//LED 1 Pin
#define LED5			P1.0				//LED 1 Pin
#define LED4			P1.3				//LED 1 Pin
#define LED3			P1.4				//Led 2 Pin
#define LED2			P1.5				//Led 3 Pin
#define LED1			P1.6

void app_init_leds(void);
void Stop_Mode(void);

#endif
