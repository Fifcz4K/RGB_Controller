#include "device_control.h"

static void rgbController(void)
{
    while(1)
    {
        vTaskDelay(100 / portTICK_RATE_MS);
        outputs_setPWM(0, getDeviceConfig()->rgbOne.red);
        outputs_setPWM(1, getDeviceConfig()->rgbOne.green);
    }
}

void deviceControlInit(void)
{
    xTaskCreate(rgbController, "rgbController", 4096, NULL, 3, NULL);
}