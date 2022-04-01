#ifndef _ADC_LIGHT_VALUES_H_
#define _ADC_LIGHT_VALUES_H_

#include "common.h"

static const uint8_t adc_light_values[] = 
{
    1,
    2,
    3
};

#define ADC_LIGHT_VALUES_ARRAY_SIZE (sizeof(adc_light_values) / sizeof(adc_light_values[0]))

int8_t adcLightValueGet(uint8_t index)
{
    return adc_light_values[index];
}

#endif