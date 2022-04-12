#include "device_task_handler.h"

static const char *TAG = "DEVICE_TASK_HANDLER.C";

static void (*rgbCallbackSectionOne)(rgb_section_t section);
static void (*rgbCallbackSectionTwo)(rgb_section_t section);
static TaskHandle_t rgbTaskHandle[rgbNumberOfSections] = {NULL};

static void rgbTaskSectionOne(void)
{
    while(1)
    {
        rgbCallbackSectionOne(rgbSectionOne);
        DELAY(rgbProgramConfigGetDelay(rgbSectionOne));
    }
}

static void rgbTaskSectionTwo(void)
{
    while(1)
    {
        rgbCallbackSectionTwo(rgbSectionTwo);
        DELAY(rgbProgramConfigGetDelay(rgbSectionTwo));
    }
}

void rgbTasksController(void)
{
    rgb_program_number_t rgbProgramSectionOne = deviceConfigGetProgram(rgbSectionOne);
    rgb_program_number_t rgbProgramSectionTwo = deviceConfigGetProgram(rgbSectionTwo);

    for(uint8_t i = 0; i < rgbNumberOfSections; i++)
    {
        if(rgbTaskHandle[i])
        {
            vTaskDelete(rgbTaskHandle[i]);
            rgbTaskHandle[i] = NULL;
        }
    }

    rgbCallbackSectionOne = rgbGetProgramFunction(rgbProgramSectionOne);
    rgbCallbackSectionTwo = rgbGetProgramFunction(rgbProgramSectionTwo);

    if(rgbCallbackSectionOne != NULL)
    {
        if(rgbProgramSectionOne == rgbProgram0)
        {
            rgbCallbackSectionOne(rgbSectionOne);
        }
        else
        {
            xTaskCreate(rgbTaskSectionOne, "rgbTaskSectionOne", 4096, NULL, 3, &rgbTaskHandle[rgbSectionOne]);
        }
    }

    if(rgbCallbackSectionTwo != NULL)
    {
        if(rgbProgramSectionTwo == rgbProgram0)
        {
            rgbCallbackSectionTwo(rgbSectionTwo);
        }
        else
        {
            xTaskCreate(rgbTaskSectionTwo, "rgbTaskSectionTwo", 4096, NULL, 3, rgbTaskHandle[rgbSectionTwo]);
        }
    }
}
