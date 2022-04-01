#ifndef _F_ADC_H_
#define _F_ADC_H_

#include "common.h"

typedef enum
{
    adcTemperatureChannel,
    adcLightChannel
}adc_channel_t;

typedef uint16_t adc_value_t;

adc_value_t adcGetValue(adc_channel_t channel);

#endif