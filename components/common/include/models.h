#ifndef _MODELS_H_
#define _MODELS_H_

#include "stdint.h"

#define FALSE 0
#define TRUE 1

typedef uint8_t color_value_t;

typedef struct
{
    uint16_t temperature;
    uint8_t light;
}measurements_t;

typedef enum
{
    Red,
    Green,
    Blue,
    NumberOfColors
}color_t;

typedef struct
{
    color_value_t color[NumberOfColors];
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

typedef enum
{
    rgbProgram0,
    rgbProgram1,
    rgbProgram2,
    rgbProgram3,
    rgbProgram4,
    rgbNumberOfPrograms
}rgb_program_t;

typedef struct
{
    rgb_t rgb[rgbNumberOfSections];
    rgb_program_t program;
    light_sensor_t lightSensor;
}device_configuration_t;

#endif