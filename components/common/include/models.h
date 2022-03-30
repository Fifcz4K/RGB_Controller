#ifndef _MODELS_H_
#define _MODELS_H_

#include "stdint.h"

#define FALSE 0
#define TRUE 1

typedef uint8_t color_value_t;

typedef struct
{
    uint16_t adcTemperature;
    uint16_t adcLight;
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
    lightSensorOff = 0xA5,
    lightSensorOn = 0xAA,
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

#endif