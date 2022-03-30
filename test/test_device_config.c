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
    deviceConfigSetRGB(rgbSectionOne, 100, 20, 30);
    checkRGBValues(100, 20, 30, 0, 0, 0);
    deviceConfigSetRGB(rgbSectionTwo, 50, 155, 255);
    checkRGBValues(100, 20, 30, 50, 155, 255);
}

void test_setting_light_sensor(void)
{
    TEST_ASSERT_EQUAL(lightSensorOff, deviceConfigGetLightSensor());
    deviceConfigSetLightSensor(lightSensorOn);
    TEST_ASSERT_EQUAL(lightSensorOn, deviceConfigGetLightSensor());
    deviceConfigSetLightSensor(lightSensorOff);
    TEST_ASSERT_EQUAL(lightSensorOff, deviceConfigGetLightSensor());
}








