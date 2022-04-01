#ifndef _ADC_H_
#define _ADC_H_

#include "common.h"

#define ADC_TEMPERATURE_CHANNEL 0
#define ADC_LIGHT_CHANNEL 1
typedef uint8_t adc_channel_t;
typedef uint16_t adc_value_t;

adc_value_t adcGetValue(adc_channel_t channel);

#endif