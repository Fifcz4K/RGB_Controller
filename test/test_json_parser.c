#include "unity.h"

#include "json_parser.h"
#include "cJSON.h"
#include "device_config.h"
#include "wifi_credentials.h"

#define DEFAULT_R1 5
#define DEFAULT_G1 10
#define DEFAULT_B1 15
#define DEFAULT_R2 175
#define DEFAULT_G2 200
#define DEFAULT_B2 255
#define DEFAULT_LIGHT_SENSOR lightSensorOn
#define DEFAULT_PROGRAM_1 rgbProgram2
#define DEFAULT_PROGRAM_2 rgbProgram3


void setUp(void)
{
    deviceConfigSetRGB(rgbSectionOne, DEFAULT_R1, DEFAULT_G1, DEFAULT_B1);
    deviceConfigSetRGB(rgbSectionTwo, DEFAULT_R2, DEFAULT_G2, DEFAULT_B2);
    deviceConfigSetLightSensor(DEFAULT_LIGHT_SENSOR);
    deviceConfigSetProgram(rgbSectionOne, DEFAULT_PROGRAM_1);
    deviceConfigSetProgram(rgbSectionTwo, DEFAULT_PROGRAM_2);
    rgbProgramsConfigInit();
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
    rgb_program_number_t programSectionOne,
    rgb_program_number_t programSectionTwo)
{
    TEST_ASSERT_EQUAL(r1, deviceConfigGetColor(rgbSectionOne, Red));
    TEST_ASSERT_EQUAL(g1, deviceConfigGetColor(rgbSectionOne, Green));
    TEST_ASSERT_EQUAL(b1, deviceConfigGetColor(rgbSectionOne, Blue));

    TEST_ASSERT_EQUAL(r2, deviceConfigGetColor(rgbSectionTwo, Red));
    TEST_ASSERT_EQUAL(g2, deviceConfigGetColor(rgbSectionTwo, Green));
    TEST_ASSERT_EQUAL(b2, deviceConfigGetColor(rgbSectionTwo, Blue));

    TEST_ASSERT_EQUAL(lightSensor, deviceConfigGetLightSensor());

    TEST_ASSERT_EQUAL(programSectionOne, deviceConfigGetProgram(rgbSectionOne));
    TEST_ASSERT_EQUAL(programSectionTwo, deviceConfigGetProgram(rgbSectionTwo));
}

void test_parse_set_config_pass_1(void)
{
    char* jsonToParse = "{  \
        \"RGB1\":           \
            {               \
            \"Prog\": 2     \
            }               \
        \"LiSen\": true     \
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
    rgbProgram2,
    DEFAULT_PROGRAM_2);
}

void test_parse_set_config_pass_2(void)
{
    char* jsonToParse = "{  \
        \"RGB2\":           \
            {               \
            \"Prog\": 4     \
            },              \
        \"LiSen\": false    \
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
    DEFAULT_PROGRAM_1,
    rgbProgram4);
}

void test_parse_set_config_pass_3(void)
{
    char *jsonToParse = "{  \
    \"RGB1\":               \
    {                       \
        \"G\": 25,          \
        \"B\" : 255,        \
        \"Prog\": 0         \
    },                      \
    \"RGB2\":               \
    {                       \
        \"Prog\": 1         \
    },                      \
    \"LiSen\": true         \
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
    rgbProgram0,
    rgbProgram1);
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
    DEFAULT_PROGRAM_1,
    DEFAULT_PROGRAM_2);
}

void test_parse_set_config_pass_5(void)
{
    char *jsonToParse = "{  \
    \"RGB2\":               \
    {                       \
        \"B\": 3            \
    }                       \
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
    DEFAULT_PROGRAM_1,
    DEFAULT_PROGRAM_2);
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
    DEFAULT_PROGRAM_1,
    DEFAULT_PROGRAM_2);
}

void test_parse_set_config_fail_2(void)
{
    char *jsonToParse = "{  \
    \"RGB1\":               \
    {                       \
        \"Prog\": 10        \
    },                      \
    \"LiSen\": true         \
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
    DEFAULT_PROGRAM_1,
    DEFAULT_PROGRAM_2);
}

void test_parse_set_rgb_program_config_pass_1(void)
{
    char* jsonToParse = "{  \
        \"S1\":             \
            {               \
            \"Del\": 50,    \
            \"Max\": 252    \
            },              \
        \"S2\":             \
            {               \
            \"Del\": 99,    \
            \"Max\": 5      \
            }               \
        }";

    jsonParseSetRgbProgramConfiguration(jsonToParse);

    TEST_ASSERT_EQUAL(50, rgbProgramConfigGetDelay(rgbSectionOne));
    TEST_ASSERT_EQUAL(252, rgbProgramConfigGetMaxValue(rgbSectionOne));
    TEST_ASSERT_EQUAL(99, rgbProgramConfigGetDelay(rgbSectionTwo));
    TEST_ASSERT_EQUAL(5, rgbProgramConfigGetMaxValue(rgbSectionTwo));
}

void test_parse_set_rgb_program_config_pass_2(void)
{
    char* jsonToParse = "{  \
        \"S2\":             \
            {               \
            \"Del\": 1000,  \
            \"Max\": 1000   \
            }               \
        }";

    jsonParseSetRgbProgramConfiguration(jsonToParse);

    TEST_ASSERT_EQUAL(PROGRAM_CONFIG_DELAY_INIT_VALUE, rgbProgramConfigGetDelay(rgbSectionOne));
    TEST_ASSERT_EQUAL(PROGRAM_CONFIG_MAX_VALUE_INIT_VALUE, rgbProgramConfigGetMaxValue(rgbSectionOne));
    TEST_ASSERT_EQUAL(1000, rgbProgramConfigGetDelay(rgbSectionTwo));
    TEST_ASSERT_EQUAL(1000 % 256, rgbProgramConfigGetMaxValue(rgbSectionTwo));
}

void test_parse_set_wifi_pass(void)
{
    char* jsonToParse = "{          \
        \"ssid\": \"MyWifi123\",    \
        \"pass\": \"MyPass123\"     \
        }";

    TEST_ASSERT_EQUAL(jsonParseOk, jsonParseWifi(jsonToParse));

    TEST_ASSERT_EQUAL_STRING("MyWifi123", wifiGetSsid());
    TEST_ASSERT_EQUAL_STRING("MyPass123", wifiGetPassword());
}

void test_parse_set_wifi_fail_1(void)
{
    char* jsonToParse = "{          \
        \"pass\": \"MyPass123\"     \
        }";

    TEST_ASSERT_EQUAL(jsonParseErr, jsonParseWifi(jsonToParse));
}

void test_parse_set_wifi_fail_2(void)
{
    char* jsonToParse = "{          \
        \"ssid\": \"MySsid123\"     \
        }";

    TEST_ASSERT_EQUAL(jsonParseErr, jsonParseWifi(jsonToParse));
}


