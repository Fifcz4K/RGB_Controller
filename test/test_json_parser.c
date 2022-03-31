#include "unity.h"

#include "device_config.h"
#include "json_parser.h"
#include "cJSON.h"

void setUp(void)
{
}

void tearDown(void)
{
    
}

void test_init(void)
{
    device_configuration_t config = {0};
    printf("sizeof: %d\n", sizeof(config));
    // char* jsonToParse = "{\"RGB1\":{\"R\":5}}";
    char* jsonToParse = "{\"LiSen\": true, \"Prog\": 2}";
    jsonParseSetConfiguration(jsonToParse, &config);
    // TEST_ASSERT_EQUAL(5, config.rgb[rgbSectionOne].color[Red]);
    TEST_ASSERT_EQUAL(rgbProgram2, config.program);
    TEST_ASSERT_EQUAL(lightSensorOn, config.lightSensor);
}








