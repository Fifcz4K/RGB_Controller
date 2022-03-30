#ifndef _DEVICE_CONFIG_H_
#define _DEVICE_CONFIG_H_

#include "models.h"

void deviceConfigInit(void);
void deviceConfigSetRGB(rgb_section_t section, color_value_t red, color_value_t green, color_value_t blue);
void deviceConfigSetLightSensor(light_sensor_t value);
light_sensor_t deviceConfigGetLightSensor(void);
color_value_t deviceConfigGetColor(rgb_section_t section, color_t color);

#endif