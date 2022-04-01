#include "unity.h"

#include "measurements.h"
#include "mock_f_adc.h"

#define MIN_ADC_VALUE 0
#define MAX_ADC_VALUE 4095 // (2 ^ adc_resolution) - 1
#define MAX_TEMPERATURE_VALUE (550 + MIN_TEMPERATURE_VALUE) // 550 = elements in adc_temperature_values[] - 1
#define ADC_TEMPERATURE_VALUES_SECOND_ELEMENT 607
#define ADC_TEMPERATURE_VALUES_ELEMENT_ONE_BEFORE_LAST 2857

void setUp(void)
{

}

void tearDown(void)
{
    
}

void test_temperature_min_adc_value(void)
{
    adc_value_t adcValue = MIN_ADC_VALUE;
    temperature_t expectedTemperature = MIN_TEMPERATURE_VALUE;
    adcGetValue_ExpectAndReturn(adcTemperatureChannel, adcValue);

    measurementProcess(measureTemperature);

    TEST_ASSERT_EQUAL(expectedTemperature, measurementTemperatureGet());
}

void test_temperature_max_adc_value(void)
{
    adc_value_t adcValue = MAX_ADC_VALUE;
    temperature_t expectedTemperature = MAX_TEMPERATURE_VALUE;
    adcGetValue_ExpectAndReturn(adcTemperatureChannel, adcValue);

    measurementProcess(measureTemperature);

    TEST_ASSERT_EQUAL(expectedTemperature, measurementTemperatureGet());
}

void test_temperature_second_adc_value(void)
{
    adc_value_t adcValue = ADC_TEMPERATURE_VALUES_SECOND_ELEMENT;
    temperature_t expectedTemperature = MIN_TEMPERATURE_VALUE + 1;
    adcGetValue_ExpectAndReturn(adcTemperatureChannel, adcValue);

    measurementProcess(measureTemperature);

    TEST_ASSERT_EQUAL(expectedTemperature, measurementTemperatureGet());
}

void test_temperature_adc_value_one_before_last(void)
{
    adc_value_t adcValue = ADC_TEMPERATURE_VALUES_ELEMENT_ONE_BEFORE_LAST;
    temperature_t expectedTemperature = MAX_TEMPERATURE_VALUE - 1;
    adcGetValue_ExpectAndReturn(adcTemperatureChannel, adcValue);

    measurementProcess(measureTemperature);

    TEST_ASSERT_EQUAL(expectedTemperature, measurementTemperatureGet());
}

void test_temperature_random_value_1(void)
{
    adc_value_t adcValue = 2000;
    temperature_t expectedTemperature = 238;
    adcGetValue_ExpectAndReturn(adcTemperatureChannel, adcValue);

    measurementProcess(measureTemperature);

    TEST_ASSERT_EQUAL(expectedTemperature, measurementTemperatureGet());
}

void test_temperature_random_value_2(void)
{
    adc_value_t adcValue = 783;
    temperature_t expectedTemperature = -44;
    adcGetValue_ExpectAndReturn(adcTemperatureChannel, adcValue);

    measurementProcess(measureTemperature);

    TEST_ASSERT_EQUAL(expectedTemperature, measurementTemperatureGet());
}