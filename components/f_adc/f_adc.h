#ifndef _F_ADC_H_
#define _F_ADC_H_

#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "common.h"

#define ADC_DEFAULT_VREF    3300
#define ADC_NO_OF_SAMPLES   8
#define ADC_WIDTH           ADC_WIDTH_BIT_12
#define ADC_ATTEN           ADC_ATTEN_DB_11
#define ADC_UNIT            ADC_UNIT_1

typedef enum
{
    adcTemperatureChannel = ADC_CHANNEL_4,
    adcLightChannel = ADC_CHANNEL_5
}channel_adc_t;

typedef uint32_t adc_value_t;

void adcInit(void);
adc_value_t adcGetValue(channel_adc_t channel);

#endif