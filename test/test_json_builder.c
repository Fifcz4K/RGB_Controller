#include "unity.h"

#include "json_builder.h"
#include "cJSON.h"
#include "device_config.h"
#include "json_parser.h"

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

    cJSON *jsonBuilded = jsonBuildConfiguration();

    deviceConfigInit(); // reset device configuration

    if(jsonParseSetConfiguration(cJSON_Print(jsonBuilded)) == jsonParseErr)
        TEST_FAIL();

    deviceConfigGet(&parsedDeviceConfig);

    TEST_ASSERT_EQUAL_MEMORY(&expectedDeviceConfig, &parsedDeviceConfig, sizeof(device_configuration_t));
}

void test_build_get_config_1(void)
{
    deviceConfigSetRGB(rgbSectionOne, 10, 15, 25);
    deviceConfigSetRGB(rgbSectionTwo, 100, 200, 255);
    deviceConfigSetLightSensor(lightSensorOn);
    deviceConfigSetProgram(rgbProgram1);

    buildParseAndCompare();
}

void test_build_get_config_2(void)
{
    deviceConfigSetRGB(rgbSectionOne, 255, 255, 255);
    deviceConfigSetRGB(rgbSectionTwo, 255, 255, 255);
    deviceConfigSetLightSensor(lightSensorOff);
    deviceConfigSetProgram(rgbProgram4);

    buildParseAndCompare();
}

void test_build_get_config_3(void)
{
    deviceConfigSetRGB(rgbSectionOne, 0, 0, 0);
    deviceConfigSetRGB(rgbSectionTwo, 0, 0, 0);
    deviceConfigSetLightSensor(lightSensorOn);
    deviceConfigSetProgram(rgbProgram0);

    buildParseAndCompare();
}





