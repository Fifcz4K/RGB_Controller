#ifndef _DEVICE_TASK_HANDLER_H_
#define _DEVICE_TASK_HANDLER_H_

#include <esp_event.h>

#include "common.h"
#include "f_adc.h"
#include "measurements.h"

#define TASK_TEMPERATURE_MEASUREMENT_DELAY 5000
#define TASK_LIGHT_MEASUREMENT_DELAY 100

typedef struct
{
    channel_adc_t channel;
    measurement_command_t command;
    uint32_t delay;
}task_handler_measurement_parameters_t;


void taskHandlerRGB(void);
void taskHandlerMeasurements(void);

#endif