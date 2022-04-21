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



