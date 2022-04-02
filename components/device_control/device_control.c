#include "device_control.h"

static void setRgbPwms(void)
{
    outputs_setPWM(RGB_OUTPUT_RED_1, deviceConfigGetColor(rgbSectionOne, Red));
    outputs_setPWM(RGB_OUTPUT_GREEN_1, deviceConfigGetColor(rgbSectionOne, Green));
    outputs_setPWM(RGB_OUTPUT_BLUE_1, deviceConfigGetColor(rgbSectionOne, Blue));

    outputs_setPWM(RGB_OUTPUT_RED_2, deviceConfigGetColor(rgbSectionTwo, Red));
    outputs_setPWM(RGB_OUTPUT_GREEN_2, deviceConfigGetColor(rgbSectionTwo, Green));
    outputs_setPWM(RGB_OUTPUT_BLUE_2, deviceConfigGetColor(rgbSectionTwo, Blue));
}

static void rgbController(void)
{
    while(1)
    {
        vTaskDelay(100 / portTICK_RATE_MS);
        setRgbPwms();
    }
}

void deviceControlInit(void)
{
    xTaskCreate(rgbController, "rgbController", 4096, NULL, 3, NULL);
}