#ifndef _OUTPUTS_H_
#define _OUTPUTS_H_

#include "driver/gpio.h"

#define GPIO_ON 0
#define GPIO_OFF 1

#define GPIO_R1  5
#define GPIO_G1  0
#define GPIO_B1  0
#define GPIO_R2  0
#define GPIO_G2  0
#define GPIO_B2  0

#define GPIO_RGB_TRANSISTORS_SEL (1ULL << GPIO_R1)// | (1ULL << GPIO_G1) | (1ULL << GPIO_B1) | (1ULL << GPIO_R2) | (1ULL << GPIO_G2) | (1ULL << GPIO_B2)

void outputs_init(void);

#endif