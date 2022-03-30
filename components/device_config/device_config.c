#include "device_config.h"

static const char *TAG = "DEVICE_CONFIG.C";

static device_configuration_t config;

void deviceConfigInit(void)
{
    for(uint8_t i = 0; i < SECTION_NUMBER; i++)
    {
        for(uint8_t j = 0; j < COLOR_NUMBER; j++)
        {
            config.rgb[i].color[j] = 0;
        }
    }

    config.lightSensor = lightSensorOff;
}

void deviceConfigSetRGB(rgb_section_t section, color_value_t red, color_value_t green, color_value_t blue)
{
    config.rgb[section].color[Red] = red;
    config.rgb[section].color[Green] = green;
    config.rgb[section].color[Blue] = blue;
}

void deviceConfigSetLightSensor(light_sensor_t value)
{
    config.lightSensor = value;
}

light_sensor_t deviceConfigGetLightSensor(void)
{
    return config.lightSensor;
}

color_value_t deviceConfigGetColor(rgb_section_t section, color_t color)
{
    return config.rgb[section].color[color];
}

