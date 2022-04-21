#ifndef _COMMON_H
#define _COMMON_H

#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"

#define DELAY(delay) vTaskDelay(delay / portTICK_RATE_MS)

#define FALSE 0
#define TRUE 1

typedef uint8_t color_value_t;
typedef int16_t temperature_value_t;
typedef uint8_t light_value_t;
typedef uint32_t adc_value_t;

#endif