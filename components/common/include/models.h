#ifndef _MODELS_H_
#define _MODELS_H_

#include "stdint.h"

#define FALSE 0
#define TRUE 1

typedef struct
{
    uint16_t adcTemperature;
    uint16_t adcLight;
}measurements_t;

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}rgb_t;

typedef struct
{
    rgb_t rgbOne;
    rgb_t rgbTwo;
    uint8_t lightSensor;
}control_t;

#endif