#ifndef _MEASUREMENTS_H_
#define _MEASUREMENTS_H_

#include "common.h"
#include "models.h"

#define MIN_TEMPERATURE_VALUE (-100)    // -100 = -10*C
#define TEMPERATURE_OFFSET (-164)       // because of PCB issue

void measurementProcess(measurement_command_t command, uint16_t adcValue);

light_t measurementLightGet(void);
temperature_t measurementTemperatureGet(void);

#endif