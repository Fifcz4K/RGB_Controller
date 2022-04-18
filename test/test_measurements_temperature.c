#include "unity.h"

#include "measurements.h"

#define MIN_ADC_VALUE 0
#define MAX_ADC_VALUE 4095 // (2 ^ adc_resolution) - 1
#define MAX_TEMPERATURE_VALUE (550 + MIN_TEMPERATURE_VALUE) // 550 = elements in adc_temperature_values[] - 1

#define ADC_TEMPERATURE_VALUES_SECOND_ELEMENT 607
#define ADC_TEMPERATURE_VALUES_ELEMENT_ONE_BEFORE_LAST 2857

#define RANDOM_TEST_1_ADC_VALUE 2000
#define RANDOM_TEST_1_TEMPERATURE 238
#define RANDOM_TEST_2_ADC_VALUE 783
#define RANDOM_TEST_2_TEMPERATURE -44
#define RANDOM_TEST_3_ADC_VALUE 1112
#define RANDOM_TEST_3_TEMPERATURE 42

void setUp(void)
{

}

void tearDown(void)
{
    
}

void test_temperature_min_adc_value(void)
{
    temperature_t expectedValue = MIN_TEMPERATURE_VALUE + TEMPERATURE_OFFSET;

    measurementProcess(measureTemperature, MIN_ADC_VALUE);

    TEST_ASSERT_EQUAL(expectedValue, measurementTemperatureGet());
}

void test_temperature_max_adc_value(void)
{
    temperature_t expectedValue = MAX_TEMPERATURE_VALUE + TEMPERATURE_OFFSET;

    measurementProcess(measureTemperature, MAX_ADC_VALUE);

    TEST_ASSERT_EQUAL(expectedValue, measurementTemperatureGet());
}

void test_temperature_second_adc_value(void)
{
    temperature_t expectedTemperature = MIN_TEMPERATURE_VALUE + 1 + TEMPERATURE_OFFSET;

    measurementProcess(measureTemperature, ADC_TEMPERATURE_VALUES_SECOND_ELEMENT);

    TEST_ASSERT_EQUAL(expectedTemperature, measurementTemperatureGet());
}

void test_temperature_adc_value_one_before_last(void)
{
    temperature_t expectedTemperature = MAX_TEMPERATURE_VALUE - 1 + TEMPERATURE_OFFSET;

    measurementProcess(measureTemperature, ADC_TEMPERATURE_VALUES_ELEMENT_ONE_BEFORE_LAST);

    TEST_ASSERT_EQUAL(expectedTemperature, measurementTemperatureGet());
}

void test_temperature_random_value_1(void)
{
    temperature_t expectedValue = RANDOM_TEST_1_TEMPERATURE + TEMPERATURE_OFFSET;
    
    measurementProcess(measureTemperature, RANDOM_TEST_1_ADC_VALUE);

    TEST_ASSERT_EQUAL(expectedValue, measurementTemperatureGet());
}

void test_temperature_random_value_2(void)
{
    temperature_t expectedValue = RANDOM_TEST_2_TEMPERATURE + TEMPERATURE_OFFSET;

    measurementProcess(measureTemperature, RANDOM_TEST_2_ADC_VALUE);

    TEST_ASSERT_EQUAL(expectedValue, measurementTemperatureGet());
}

void test_temperature_random_value_3(void)
{
    temperature_t expectedValue = RANDOM_TEST_3_TEMPERATURE + TEMPERATURE_OFFSET;

    measurementProcess(measureTemperature, RANDOM_TEST_3_ADC_VALUE);

    TEST_ASSERT_EQUAL(expectedValue, measurementTemperatureGet());
}
