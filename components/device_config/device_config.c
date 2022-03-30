#include "device_config.h"

static const char *TAG = "DEVICE_CONFIG.C";

static device_configuration_t config;

void deviceConfigInit(void)
{
    for(uint8_t i = 0; i < rgbNumberOfSections; i++)
    {
        for(uint8_t j = 0; j < NumberOfColors; j++)
        {
            config.rgb[i].color[j] = 0;
        }
    }

    config.lightSensor = lightSensorOff;
}

bool deviceConfigSetRGB(rgb_section_t section, color_value_t red, color_value_t green, color_value_t blue)
{
    if(section >= rgbNumberOfSections)
        return false;

    config.rgb[section].color[Red] = red;
    config.rgb[section].color[Green] = green;
    config.rgb[section].color[Blue] = blue;

    return true;
}

bool deviceConfigSetLightSensor(light_sensor_t value)
{
    if(value != lightSensorOn && value != lightSensorOff)
        return false;

    config.lightSensor = value;

    return true;
}

light_sensor_t deviceConfigGetLightSensor(void)
{
    return config.lightSensor;
}

color_value_t deviceConfigGetColor(rgb_section_t section, color_t color)
{
    return config.rgb[section].color[color];
}

