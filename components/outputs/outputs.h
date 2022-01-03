#ifndef _OUTPUTS_H_
#define _OUTPUTS_H_

#include "driver/ledc.h"

#define GPIO_R1  5
#define GPIO_G1  4//18
#define GPIO_B1  0
#define GPIO_R2  0
#define GPIO_G2  0
#define GPIO_B2  0

#define LEDC_LS_TIMER          LEDC_TIMER_1
#define LEDC_LS_MODE           LEDC_LOW_SPEED_MODE

#define LEDC_LS_CH0_GPIO       (GPIO_R1)
#define LEDC_LS_CH0_CHANNEL    LEDC_CHANNEL_0
#define LEDC_LS_CH1_GPIO       (GPIO_G1)
#define LEDC_LS_CH1_CHANNEL    LEDC_CHANNEL_1

#define LEDC_TEST_CH_NUM       (2)

void outputs_init(void);
void outputs_setPWM(uint8_t channel, uint8_t colorValue);

#endif