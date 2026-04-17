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
void app_configure_callbacks(void);
void app_configure_mode_profile(void);
void app_configure_protection(void);
void app_configure_hw_protection_path(void);
void app_configure_thermistor_tables(void);
void app_apply_calibration_profiles(void);
void app_process_ad_measurement_api(void);
void app_process_cc_measurement_api(void);
void app_process_measurement_api(void);
void app_poll_ad_raw_signal(void);
void app_poll_cc_raw_signal(void);
void app_poll_fast_signals(void);
void app_refresh_fet_status(void);
void app_service_mode_manager(void);
void app_service_balancing_control(void);
void app_service_fet_override(void);
void app_service_latched_protection(void);
void Stop_Mode(void);

#endif
