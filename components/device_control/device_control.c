#include "device_control.h"

static void blink(void)
{
    uint16_t counter = 0;
    while(1)
    {
        vTaskDelay(1000 / portTICK_RATE_MS);
        gpio_set_level(GPIO_R1, counter % 2);   
        gpio_set_level(GPIO_G1, counter++ % 4);   
    }
}

void deviceControlInit(void)
{
    xTaskCreate(blink, "blink", 4096, NULL, 3, NULL);
}