#ifndef _MODELS_H_
#define _MODELS_H_

#include "stdint.h"

#define FALSE 0
#define TRUE 1

#define SECTION_NUMBER 2
#define COLOR_NUMBER 3

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
    Blue
}color_t;

typedef struct
{
    color_value_t color[COLOR_NUMBER];
}rgb_t;

typedef enum
{
    lightSensorOff = 0xA5,
    lightSensorOn = 0xAA,
}light_sensor_t;

typedef enum
{
    rgbSectionOne,
    rgbSectionTwo
}rgb_section_t;

typedef struct
{
    rgb_t rgb[SECTION_NUMBER];
    light_sensor_t lightSensor;
}device_configuration_t;

#endif