#ifndef _MODELS_H_
#define _MODELS_H_

#include "common.h"

typedef struct
{
    temperature_t temperature; // operating on temperature multiplied by 10 to avoid float data type
    light_t light; // 0 - 100%
}measurements_t;

typedef enum
{
    measureTemperature,
    measureLight
}measurement_command_t;

typedef enum
{
    Red,
    Green,
    Blue,
    NumberOfColors
}color_t;

typedef enum
{
    rgbProgram0,
    rgbProgram1,
    rgbProgram2,
    rgbProgram3,
    rgbProgram4,
    rgbNumberOfPrograms
}rgb_program_number_t;

typedef struct
{
    color_value_t color[NumberOfColors];
    rgb_program_number_t program;
}rgb_t;

typedef enum
{
    lightSensorOff,
    lightSensorOn
}light_sensor_t;

typedef enum
{
    rgbSectionOne,
    rgbSectionTwo,
    rgbNumberOfSections
}rgb_section_t;

typedef struct
{
    rgb_t rgb[rgbNumberOfSections];
    light_sensor_t lightSensor;
}device_configuration_t;

typedef struct
{
    uint16_t delay;
    color_value_t maxValue;
}rgb_program_configuration_t;


#endif