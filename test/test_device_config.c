#include "unity.h"
#include "device_config.h"

void setUp(void)
{
    deviceConfigInit();
}

void tearDown(void)
{
}

void test_init(void)
{
    TEST_ASSERT_EQUAL(0, deviceConfigGetColor(rgbSectionOne, Red));
    TEST_ASSERT_EQUAL(0, deviceConfigGetColor(rgbSectionOne, Green));
    TEST_ASSERT_EQUAL(0, deviceConfigGetColor(rgbSectionOne, Blue));

    TEST_ASSERT_EQUAL(0, deviceConfigGetColor(rgbSectionTwo, Red));
    TEST_ASSERT_EQUAL(0, deviceConfigGetColor(rgbSectionTwo, Green));
    TEST_ASSERT_EQUAL(0, deviceConfigGetColor(rgbSectionTwo, Blue));

    TEST_ASSERT_EQUAL(rgbProgram0, deviceConfigGetProgram(rgbSectionOne));
    TEST_ASSERT_EQUAL(rgbProgram0, deviceConfigGetProgram(rgbSectionTwo));
    TEST_ASSERT_EQUAL(lightSensorOff, deviceConfigGetLightSensor());
}

static void checkRGBValues(color_t r1, color_t g1, color_t b1, color_t r2, color_t g2, color_t b2)
{
    TEST_ASSERT_EQUAL(r1, deviceConfigGetColor(rgbSectionOne, Red));
    TEST_ASSERT_EQUAL(g1, deviceConfigGetColor(rgbSectionOne, Green));
    TEST_ASSERT_EQUAL(b1, deviceConfigGetColor(rgbSectionOne, Blue));

    TEST_ASSERT_EQUAL(r2, deviceConfigGetColor(rgbSectionTwo, Red));
    TEST_ASSERT_EQUAL(g2, deviceConfigGetColor(rgbSectionTwo, Green));
    TEST_ASSERT_EQUAL(b2, deviceConfigGetColor(rgbSectionTwo, Blue));
}

void test_setting_colors(void)
{
    checkRGBValues(0, 0, 0, 0, 0, 0);

    TEST_ASSERT_EQUAL(true, deviceConfigSetRGB(rgbSectionOne, 100, 20, 30));
    checkRGBValues(100, 20, 30, 0, 0, 0);

    TEST_ASSERT_EQUAL(true, deviceConfigSetRGB(rgbSectionTwo, 50, 155, 255));
    checkRGBValues(100, 20, 30, 50, 155, 255);

    TEST_ASSERT_EQUAL(false, deviceConfigSetRGB(rgbNumberOfSections, 0, 1, 2));
    checkRGBValues(100, 20, 30, 50, 155, 255);
}

void test_setting_light_sensor(void)
{
    TEST_ASSERT_EQUAL(lightSensorOff, deviceConfigGetLightSensor());

    TEST_ASSERT_EQUAL(true, deviceConfigSetLightSensor(lightSensorOn));
    TEST_ASSERT_EQUAL(lightSensorOn, deviceConfigGetLightSensor());
    
    TEST_ASSERT_EQUAL(false, deviceConfigSetLightSensor(2));
    TEST_ASSERT_EQUAL(false, deviceConfigSetLightSensor(255));
    TEST_ASSERT_EQUAL(lightSensorOn, deviceConfigGetLightSensor());

    TEST_ASSERT_EQUAL(true, deviceConfigSetLightSensor(lightSensorOff));
    TEST_ASSERT_EQUAL(lightSensorOff, deviceConfigGetLightSensor());
}

void test_setting_program(void)
{
    TEST_ASSERT_EQUAL(rgbProgram0, deviceConfigGetProgram(rgbSectionOne));
    TEST_ASSERT_EQUAL(rgbProgram0, deviceConfigGetProgram(rgbSectionTwo));

    TEST_ASSERT_EQUAL(true, deviceConfigSetProgram(rgbSectionOne, rgbProgram1));
    TEST_ASSERT_EQUAL(rgbProgram1, deviceConfigGetProgram(rgbSectionOne));

    TEST_ASSERT_EQUAL(true, deviceConfigSetProgram(rgbSectionTwo, rgbProgram3));
    TEST_ASSERT_EQUAL(rgbProgram3, deviceConfigGetProgram(rgbSectionTwo));

    TEST_ASSERT_EQUAL(true, deviceConfigSetProgram(rgbSectionOne, rgbProgram4));
    TEST_ASSERT_EQUAL(rgbProgram4, deviceConfigGetProgram(rgbSectionOne));

    TEST_ASSERT_EQUAL(true, deviceConfigSetProgram(rgbSectionTwo, rgbProgram2));
    TEST_ASSERT_EQUAL(rgbProgram2, deviceConfigGetProgram(rgbSectionTwo));

    TEST_ASSERT_EQUAL(false, deviceConfigSetProgram(rgbSectionOne, rgbNumberOfPrograms));
    TEST_ASSERT_EQUAL(rgbProgram4, deviceConfigGetProgram(rgbSectionOne));

    TEST_ASSERT_EQUAL(false, deviceConfigSetProgram(rgbSectionTwo, rgbNumberOfPrograms));
    TEST_ASSERT_EQUAL(rgbProgram2, deviceConfigGetProgram(rgbSectionTwo));

    TEST_ASSERT_EQUAL(false, deviceConfigSetProgram(rgbNumberOfSections, rgbProgram0));

    TEST_ASSERT_EQUAL(true, deviceConfigSetProgram(rgbSectionOne, rgbProgram3));
    TEST_ASSERT_EQUAL(rgbProgram3, deviceConfigGetProgram(rgbSectionOne));

    TEST_ASSERT_EQUAL(true, deviceConfigSetProgram(rgbSectionTwo, rgbProgram0));
    TEST_ASSERT_EQUAL(rgbProgram0, deviceConfigGetProgram(rgbSectionTwo));
}

void test_get_full_config(void)
{
    device_configuration_t configToTest = {0};

    deviceConfigSetRGB(rgbSectionOne, 10, 20, 30);
    deviceConfigSetRGB(rgbSectionTwo, 100, 155, 255);
    deviceConfigSetLightSensor(lightSensorOn);
    deviceConfigSetProgram(rgbSectionOne, rgbProgram3);
    deviceConfigSetProgram(rgbSectionTwo, rgbProgram1);

    deviceConfigGet(&configToTest);

    TEST_ASSERT_EQUAL(10, configToTest.rgb[rgbSectionOne].color[Red]);
    TEST_ASSERT_EQUAL(20, configToTest.rgb[rgbSectionOne].color[Green]);
    TEST_ASSERT_EQUAL(30, configToTest.rgb[rgbSectionOne].color[Blue]);
    TEST_ASSERT_EQUAL(100, configToTest.rgb[rgbSectionTwo].color[Red]);
    TEST_ASSERT_EQUAL(155, configToTest.rgb[rgbSectionTwo].color[Green]);
    TEST_ASSERT_EQUAL(255, configToTest.rgb[rgbSectionTwo].color[Blue]);

    TEST_ASSERT_EQUAL(lightSensorOn, configToTest.lightSensor);

    TEST_ASSERT_EQUAL(rgbProgram3, configToTest.rgb[rgbSectionOne].program);
    TEST_ASSERT_EQUAL(rgbProgram1, configToTest.rgb[rgbSectionTwo].program);
}

void test_set_full_config(void)
{
    device_configuration_t configToTest = 
    {
        .rgb[rgbSectionOne].color[Red] = 100,
        .rgb[rgbSectionOne].color[Green] = 0,
        .rgb[rgbSectionOne].color[Blue] = 255,
        .rgb[rgbSectionOne].program = rgbProgram1,
        .rgb[rgbSectionTwo].color[Red] = 88,
        .rgb[rgbSectionTwo].color[Green] = 123,
        .rgb[rgbSectionTwo].color[Blue] = 189,
        .rgb[rgbSectionTwo].program = rgbProgram4,
        .lightSensor = lightSensorOn
    };

    TEST_ASSERT_EQUAL(true, deviceConfigSet(&configToTest));

    configToTest.lightSensor = lightSensorOff;
    configToTest.rgb[rgbSectionOne].program = rgbProgram1;
    configToTest.rgb[rgbSectionTwo].program = rgbProgram4;

    TEST_ASSERT_EQUAL(true, deviceConfigSet(&configToTest));

    configToTest.lightSensor = 0x55;

    TEST_ASSERT_EQUAL(false, deviceConfigSet(&configToTest));

    configToTest.lightSensor = lightSensorOff;
    configToTest.rgb[rgbSectionOne].program = rgbNumberOfPrograms;

    TEST_ASSERT_EQUAL(false, deviceConfigSet(&configToTest));

    configToTest.rgb[rgbSectionTwo].program = rgbNumberOfPrograms;

    TEST_ASSERT_EQUAL(false, deviceConfigSet(&configToTest));
}

void test_get_set_rgb_program_config(void)
{
    rgb_program_configuration_t configToTest[rgbNumberOfSections];

    configToTest[rgbSectionOne].maxValue = 240;
    configToTest[rgbSectionOne].delay = 10;
    configToTest[rgbSectionTwo].maxValue = 15;
    configToTest[rgbSectionTwo].delay = 25;

    rgbProgramConfigSet(configToTest);

    for(uint8_t i = 0; i < rgbNumberOfSections; i++)
    {
        memset(configToTest + i, 0, sizeof(rgb_program_configuration_t));
    }

    rgbProgramConfigGet(configToTest);

    TEST_ASSERT_EQUAL(240, configToTest[rgbSectionOne].maxValue);
    TEST_ASSERT_EQUAL(10, configToTest[rgbSectionOne].delay);
    TEST_ASSERT_EQUAL(15, configToTest[rgbSectionTwo].maxValue);
    TEST_ASSERT_EQUAL(25, configToTest[rgbSectionTwo].delay);
}

