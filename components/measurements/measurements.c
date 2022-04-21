#include "measurements.h"
#include "adc_light_values.h"
#include "adc_temperature_values.h"

static measurements_t measurements;

static light_value_t measurementCountLightFromAdc(adc_value_t adcValue)
{
    //todo
    return 0;
}

static temperature_value_t measurementCountTemperatureFromAdc(adc_value_t adcValue)
{
    uint16_t adcDiff = 0xFFFF;
    uint16_t absValue = 0;
    uint16_t remember_i = 0;

    for(uint16_t i = 0; i < ADC_TEMPERATURE_VALUES_ARRAY_SIZE; i++)
    {
        absValue = abs(adcValue - adcTemperatureValueGet(i));
        if(absValue <= adcDiff)
        {
            adcDiff = absValue;
            remember_i = i;
        }
        else
        {
            break;
        }
    }

    return remember_i + MIN_TEMPERATURE_VALUE;
}

void measurementProcess(measurement_command_t command, adc_value_t adcValue)
{
    switch(command)
    {
        case measureTemperature:
            measurements.temperature = measurementCountTemperatureFromAdc(adcValue) + TEMPERATURE_OFFSET;
        break;

        case measureLight:
            measurements.light = measurementCountLightFromAdc(adcValue);
        break;

        default:
        break;
    }
}

light_value_t measurementLightGet(void)
{
    return measurements.light;
}

temperature_value_t measurementTemperatureGet(void)
{
    return measurements.temperature;
}