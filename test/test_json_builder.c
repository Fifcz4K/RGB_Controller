#include "unity.h"

#include "json_builder.h"
#include "cJSON.h"
#include "device_config.h"
#include "json_parser.h"
#include "wifi_credentials.h"
#include "mock_measurements.h"

void setUp(void)
{
    deviceConfigInit();
}

void tearDown(void)
{
    
}

static void buildParseAndCompare(void)
{
    device_configuration_t expectedDeviceConfig, parsedDeviceConfig;

    deviceConfigGet(&expectedDeviceConfig);

    char *jsonBuilded = jsonBuildConfiguration();

    deviceConfigInit(); // reset device configuration

    if(jsonParseSetConfiguration(jsonBuilded) == jsonParseErr)
        TEST_FAIL();

    deviceConfigGet(&parsedDeviceConfig);

    TEST_ASSERT_EQUAL_MEMORY(&expectedDeviceConfig, &parsedDeviceConfig, sizeof(device_configuration_t));
}

void test_build_get_config_1(void)
{
    deviceConfigSetRGB(rgbSectionOne, 10, 15, 25);
    deviceConfigSetRGB(rgbSectionTwo, 100, 200, 255);
    deviceConfigSetLightSensor(lightSensorOn);
    deviceConfigSetProgram(rgbSectionOne, rgbProgram1);
    deviceConfigSetProgram(rgbSectionTwo, rgbProgram2);

    buildParseAndCompare();
}

void test_build_get_config_2(void)
{
    deviceConfigSetRGB(rgbSectionOne, 255, 255, 255);
    deviceConfigSetRGB(rgbSectionTwo, 255, 255, 255);
    deviceConfigSetLightSensor(lightSensorOff);
    deviceConfigSetProgram(rgbSectionOne, rgbProgram3);
    deviceConfigSetProgram(rgbSectionTwo, rgbProgram1);

    buildParseAndCompare();
}

void test_build_get_config_3(void)
{
    deviceConfigSetRGB(rgbSectionOne, 0, 0, 0);
    deviceConfigSetRGB(rgbSectionTwo, 0, 0, 0);
    deviceConfigSetLightSensor(lightSensorOn);
    deviceConfigSetProgram(rgbSectionOne, rgbProgram0);
    deviceConfigSetProgram(rgbSectionTwo, rgbProgram4);

    buildParseAndCompare();
}

void test_build_get_measurements_max_values(void)
{
    char *jsonExpected = "{\n\x09\"Temp\":\x09\x34\x35\x30,\n\x09\"Light\":\x09\x31\x30\x30\n}"; // \x34\x35\x30 = 450, \x31\x30\x30 = 100

    measurementTemperatureGet_ExpectAndReturn(450);
    measurementLightGet_ExpectAndReturn(100);
  
    char *jsonMeasurements = jsonBuildMeasurements();

    TEST_ASSERT_EQUAL_STRING(jsonExpected, jsonMeasurements);
}

void test_build_get_measurements_min_values(void)
{
    char *jsonExpected = "{\n\x09\"Temp\":\x09\x2d\x31\x30\x30,\n\x09\"Light\":\x09\x30\n}"; // \x2d\x31\x30\x30 = -100, \x30 = 0

    measurementTemperatureGet_ExpectAndReturn(-100);
    measurementLightGet_ExpectAndReturn(0);
  
    char *jsonMeasurements = jsonBuildMeasurements();

    TEST_ASSERT_EQUAL_STRING(jsonExpected, jsonMeasurements);
}

void test_build_get_measurements_zeros(void)
{
    char *jsonExpected = "{\n\x09\"Temp\":\x09\x30,\n\x09\"Light\":\x09\x30\n}"; // \x30 = 0, \x30 = 0

    measurementTemperatureGet_ExpectAndReturn(0);
    measurementLightGet_ExpectAndReturn(0);
  
    char *jsonMeasurements = jsonBuildMeasurements();

    TEST_ASSERT_EQUAL_STRING(jsonExpected, jsonMeasurements);
}

void test_build_get_measurements_random_values_1(void)
{
    char *jsonExpected = "{\n\x09\"Temp\":\x09\x31\x39\x32,\n\x09\"Light\":\x09\x35\x30\n}"; // \x31\x39\x32 = 192, \x35\x30 = 50

    measurementTemperatureGet_ExpectAndReturn(192);
    measurementLightGet_ExpectAndReturn(50);
  
    char *jsonMeasurements = jsonBuildMeasurements();

    TEST_ASSERT_EQUAL_STRING(jsonExpected, jsonMeasurements);
}