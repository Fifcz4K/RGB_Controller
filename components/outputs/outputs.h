#ifndef _OUTPUTS_H_
#define _OUTPUTS_H_

#include "driver/ledc.h"
#include "stdint.h"

#define GPIO_R1  5
#define GPIO_G1  4//18
#define GPIO_B1  19
#define GPIO_R2  27
#define GPIO_G2  26
#define GPIO_B2  25

#define LEDC_LS_TIMER          LEDC_TIMER_1
#define LEDC_LS_MODE           LEDC_LOW_SPEED_MODE

#define LEDC_LS_CH0_GPIO       (GPIO_R1)
#define LEDC_LS_CH0_CHANNEL    LEDC_CHANNEL_0
#define LEDC_LS_CH1_GPIO       (GPIO_G1)
#define LEDC_LS_CH1_CHANNEL    LEDC_CHANNEL_1
#define LEDC_LS_CH2_GPIO       (GPIO_B1)
#define LEDC_LS_CH2_CHANNEL    LEDC_CHANNEL_2
#define LEDC_LS_CH3_GPIO       (GPIO_R2)
#define LEDC_LS_CH3_CHANNEL    LEDC_CHANNEL_3
#define LEDC_LS_CH4_GPIO       (GPIO_G2)
#define LEDC_LS_CH4_CHANNEL    LEDC_CHANNEL_4
#define LEDC_LS_CH5_GPIO       (GPIO_B2)
#define LEDC_LS_CH5_CHANNEL    LEDC_CHANNEL_5

#define LEDC_TEST_CH_NUM       (6)

#define PWM_RESOLUTION (8192)
#define MAX_COLOR_VALUE (255)
#define PWM_DUTY_STEP (PWM_RESOLUTION / MAX_COLOR_VALUE)

void outputs_init(void);
void outputs_setPWM(uint8_t channel, uint8_t colorValue);

#endif