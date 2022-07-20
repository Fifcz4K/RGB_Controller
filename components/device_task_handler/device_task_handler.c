#include "device_task_handler.h"

static task_handler_measurement_parameters_t temperatureMeasureTaskParam = 
{
    .channel = adcTemperatureChannel,
    .command = measureTemperature,
    .delay = TASK_TEMPERATURE_MEASUREMENT_DELAY
};

static task_handler_measurement_parameters_t lightMeasureTaskParam = 
{
    .channel = adcLightChannel,
    .command = measureLight,
    .delay = TASK_LIGHT_MEASUREMENT_DELAY
};

static void measureTask(void *param)
{
    task_handler_measurement_parameters_t *taskParameters = (task_handler_measurement_parameters_t*)param;
    adc_value_t adcValue = 0;

    while(1)
    {
        adcValue = adcGetValue(taskParameters->channel);
        measurementProcess(taskParameters->command, adcValue);
        DELAY(taskParameters->delay);
    }
}

void taskHandlerMeasurements(void)
{
    xTaskCreate(measureTask, "TemperatureMeasureTask", 4096, &temperatureMeasureTaskParam, 4, NULL);
    xTaskCreate(measureTask, "LightMeasureTask", 4096, &lightMeasureTaskParam, 4, NULL);
}

static const uint8_t rgbOutput[rgbNumberOfSections][NumberOfColors] =
{
    {RGB_OUTPUT_RED_1, RGB_OUTPUT_GREEN_1, RGB_OUTPUT_BLUE_1},
    {RGB_OUTPUT_RED_2, RGB_OUTPUT_GREEN_2, RGB_OUTPUT_BLUE_2}
};

static void rgbTask(void *param)
{
    color_value_t colorValue = 0;

    while(1)
    {
        for(uint8_t i = 0; i < rgbNumberOfSections; i++)
        {
            for(uint8_t j = 0; j < NumberOfColors; i++)
            {
                colorValue = rgbGetColorValue(i, j);
                outputs_setPWM(rgbOutput[i][j], colorValue);
            }
        }

        DELAY(1);
    }
}

void taskHandlerRGB(void)
{
    xTaskCreate(rgbTask, "rgbTask", 4096, NULL, 5, NULL);
}


