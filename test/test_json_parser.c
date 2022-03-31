#include "unity.h"

#include "json_parser.h"
#include "cJSON.h"
#include "device_config.h"

#define DEFAULT_R1 5
#define DEFAULT_G1 10
#define DEFAULT_B1 15
#define DEFAULT_R2 175
#define DEFAULT_G2 200
#define DEFAULT_B2 255
#define DEFAULT_LIGHT_SENSOR lightSensorOn
#define DEFAULT_PROGRAM rgbProgram2

void setUp(void)
{
    deviceConfigSetRGB(rgbSectionOne, DEFAULT_R1, DEFAULT_G1, DEFAULT_B1);
    deviceConfigSetRGB(rgbSectionTwo, DEFAULT_R2, DEFAULT_G2, DEFAULT_B2);
    deviceConfigSetLightSensor(DEFAULT_LIGHT_SENSOR);
    deviceConfigSetProgram(DEFAULT_PROGRAM);
}

void tearDown(void)
{
    
}

static bool checkConfig(
    color_t r1,
    color_t g1,
    color_t b1,
    color_t r2,
    color_t g2,
    color_t b2,
    light_sensor_t lightSensor,
    rgb_program_t program)
{
    TEST_ASSERT_EQUAL(r1, deviceConfigGetColor(rgbSectionOne, Red));
    TEST_ASSERT_EQUAL(g1, deviceConfigGetColor(rgbSectionOne, Green));
    TEST_ASSERT_EQUAL(b1, deviceConfigGetColor(rgbSectionOne, Blue));

    TEST_ASSERT_EQUAL(r2, deviceConfigGetColor(rgbSectionTwo, Red));
    TEST_ASSERT_EQUAL(g2, deviceConfigGetColor(rgbSectionTwo, Green));
    TEST_ASSERT_EQUAL(b2, deviceConfigGetColor(rgbSectionTwo, Blue));

    TEST_ASSERT_EQUAL(lightSensor, deviceConfigGetLightSensor());

    TEST_ASSERT_EQUAL(program, deviceConfigGetProgram());
}

void test_parse_set_config_pass_1(void)
{
    char* jsonToParse = "{  \
        \"LiSen\": true,    \
        \"Prog\": 2         \
        }";

    TEST_ASSERT_EQUAL(jsonParseOk, jsonParseSetConfiguration(jsonToParse));
    checkConfig(
    DEFAULT_R1,
    DEFAULT_G1,
    DEFAULT_B1,
    DEFAULT_R2,
    DEFAULT_G2,
    DEFAULT_B2,
    lightSensorOn,
    rgbProgram2);
}

void test_parse_set_config_pass_2(void)
{
    char* jsonToParse = "{  \
        \"LiSen\": false,    \
        \"Prog\": 4         \
        }";

    TEST_ASSERT_EQUAL(jsonParseOk, jsonParseSetConfiguration(jsonToParse));
    checkConfig(
    DEFAULT_R1, 
    DEFAULT_G1,
    DEFAULT_B1,
    DEFAULT_R2,
    DEFAULT_G2,
    DEFAULT_B2,
    lightSensorOff,
    rgbProgram4);
}

void test_parse_set_config_pass_3(void)
{
    char *jsonToParse = "{  \
    \"RGB1\":               \
    {                       \
        \"G\": 25,          \
        \"B\" : 255         \
    },                      \
    \"LiSen\": true,        \
    \"Prog\": 0             \
    }";

    TEST_ASSERT_EQUAL(jsonParseOk, jsonParseSetConfiguration(jsonToParse));
    checkConfig(
    DEFAULT_R1,
    25,
    255,
    DEFAULT_R2,
    DEFAULT_G2,
    DEFAULT_B2,
    lightSensorOn,
    rgbProgram0);
}

void test_parse_set_config_pass_4(void)
{
    char *jsonToParse = "{  \
    \"RGB1\":               \
    {                       \
        \"R\": 200,         \
        \"G\": 199          \
    },                      \
    \"RGB2\":               \
    {                       \
        \"R\": 1,           \
        \"G\": 2,           \
        \"B\": 3            \
    }                       \
    }";

    TEST_ASSERT_EQUAL(jsonParseOk, jsonParseSetConfiguration(jsonToParse));
    checkConfig(
    200, 
    199, 
    DEFAULT_B1, 
    1, 
    2, 
    3, 
    DEFAULT_LIGHT_SENSOR, 
    DEFAULT_PROGRAM);
}

void test_parse_set_config_pass_5(void)
{
    char *jsonToParse = "{  \
    \"RGB2\":               \
    {                       \
        \"B\": 3            \
    },                      \
    \"Prog\": 3             \
    }";

    TEST_ASSERT_EQUAL(jsonParseOk, jsonParseSetConfiguration(jsonToParse));
    checkConfig(
    DEFAULT_R1, 
    DEFAULT_G1, 
    DEFAULT_B1, 
    DEFAULT_R2, 
    DEFAULT_G2, 
    3, 
    DEFAULT_LIGHT_SENSOR, 
    rgbProgram3);
}

void test_parse_set_config_fail_1(void)
{
    char *jsonToParse = "{  \
    \"RGB1\":               \
    {                       \
        \"R\": 200,         \
        \"G\": 199          \
    },                      \
    \"RGB2\":               \
    {                       \
        \"R\": 1,           \
        \"G\": 2,           \
        \"B\": 3            \
    },                      \
    \"LiSen\": 5            \
    }";

    TEST_ASSERT_EQUAL(jsonParseErr, jsonParseSetConfiguration(jsonToParse));
    checkConfig(
    DEFAULT_R1, 
    DEFAULT_G1, 
    DEFAULT_B1, 
    DEFAULT_R2, 
    DEFAULT_G2, 
    DEFAULT_B2, 
    DEFAULT_LIGHT_SENSOR, 
    DEFAULT_PROGRAM);
}

void test_parse_set_config_fail_2(void)
{
    char *jsonToParse = "{  \
    \"LiSen\": true,        \
    \"Prog\": 10            \
    }";

    TEST_ASSERT_EQUAL(jsonParseErr, jsonParseSetConfiguration(jsonToParse));
    checkConfig(
    DEFAULT_R1, 
    DEFAULT_G1, 
    DEFAULT_B1, 
    DEFAULT_R2, 
    DEFAULT_G2, 
    DEFAULT_B2, 
    DEFAULT_LIGHT_SENSOR, 
    DEFAULT_PROGRAM);
}


