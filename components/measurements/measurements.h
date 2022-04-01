#ifndef _MEASUREMENTS_H_
#define _MEASUREMENTS_H_

#include "common.h"
#include "models.h"

light_t measurementCountLightFromAdc(uint16_t adcValue);
temperature_t measurementCountTemperatureFromAdc(uint16_t adcValue);

#endif