#ifndef _MEASUREMENTS_H_
#define _MEASUREMENTS_H_

#include "common.h"
#include "models.h"
#include "f_adc.h"

#define MIN_TEMPERATURE_VALUE (-100) // -100 = -10*C

void measurementProcess(measurement_command_t command);

light_t measurementLightGet(void);
temperature_t measurementTemperatureGet(void);

#endif