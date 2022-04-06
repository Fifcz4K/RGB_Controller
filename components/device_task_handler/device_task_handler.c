#include "device_task_handler.h"

static TaskHandle_t rgbTaskHandle[rgbNumberOfSections] = {NULL};

void rgbTaskController(void)
{
    for(uint8_t i = 0; i < rgbNumberOfSections; i++)
    {
        if(rgbTaskHandle[i])
            vTaskDelete(rgbTaskHandle[i]);
    }

    
}

void deviceTasksInit(void)
{
}