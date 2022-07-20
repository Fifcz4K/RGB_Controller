#ifndef RGB_CONFIGURATION_H
#define RGB_CONFIGURATION_H

#include "common.h"

typedef enum
{
    Red,
    Green,
    Blue,
    NumberOfColors
}color_t;

typedef enum
{
    rgbSectionOne,
    rgbSectionTwo,
    rgbNumberOfSections
}rgb_section_t;

typedef enum
{
    rgbIncrementing,
    rgbDecrementing
}rgb_direction_t;

typedef struct
{
    color_value_t value;
    color_value_t step;
    color_value_t minValue;
    color_value_t maxValue;
    rgb_direction_t direction;
    uint16_t delay;
}rgb_configuration_t;

void rgbInit(void);
color_value_t rgbGetColorValue(rgb_section_t section, color_t color);

#endif