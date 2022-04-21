#ifndef _MEASUREMENTS_H_
#define _MEASUREMENTS_H_

#include "common.h"

#define MIN_TEMPERATURE_VALUE (-100)    // -100 = -10*C
#define TEMPERATURE_OFFSET (-164)       // because of PCB issue

typedef struct
{
    temperature_value_t temperature; // operating on temperature multiplied by 10 to avoid float data type
    light_value_t light; // 0 - 100%
}measurements_t;

typedef enum
{
    measureTemperature,
    measureLight
}measurement_command_t;

void measurementProcess(measurement_command_t command, adc_value_t adcValue);

light_value_t measurementLightGet(void);
temperature_value_t measurementTemperatureGet(void);

#endif