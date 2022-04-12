#include "device_config.h"

static device_configuration_t config;
static rgb_program_configuration_t rgbProgramConfig[rgbNumberOfSections];

bool configChanged = false;

bool isConfigChanged(void)
{
    bool retVal = false;

    if(configChanged == true)
    {
        retVal = true;
        configChanged = false;
    }

    return retVal;
}

void deviceConfigInit(void)
{
    for(uint8_t i = 0; i < rgbNumberOfSections; i++)
    {
        for(uint8_t j = 0; j < NumberOfColors; j++)
        {
            config.rgb[i].color[j] = 0;
        }
        config.rgb[i].program = rgbProgram0;
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

bool deviceConfigSetProgram(rgb_section_t section, rgb_program_number_t program)
{
    if(program >= rgbNumberOfPrograms)
        return false;

    if(section >= rgbNumberOfSections)
        return false;

    config.rgb[section].program = program;

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

rgb_program_number_t deviceConfigGetProgram(rgb_section_t section)
{
    return config.rgb[section].program;
}

static bool deviceConfigParamsOk(light_sensor_t lightSensor, rgb_program_number_t rgbProgram1, rgb_program_number_t rgbProgram2)
{
    bool result = true;

    if(lightSensor != lightSensorOff && lightSensor != lightSensorOn)
        result = false;

    if(rgbProgram1 >= rgbNumberOfPrograms)
        result = false;

    if(rgbProgram2 >= rgbNumberOfPrograms)
        result = false;

    return result;
}

bool deviceConfigSet(device_configuration_t *tempConfig)
{
    if(deviceConfigParamsOk(tempConfig->lightSensor, tempConfig->rgb[rgbSectionOne].program, tempConfig->rgb[rgbSectionTwo].program) == false)
        return false;

    memcpy(&config, tempConfig, sizeof(device_configuration_t));

    configChanged = true;

    return true;
}

void deviceConfigGet(device_configuration_t *tempConfig)
{
    memcpy(tempConfig, &config, sizeof(device_configuration_t));
}

void rgbProgramsConfigInit(void)
{
    for(uint8_t i = 0; i < rgbNumberOfSections; i++)
    {
        rgbProgramConfig[i].delay = PROGRAM_CONFIG_DELAY_INIT_VALUE;
        rgbProgramConfig[i].maxValue = PROGRAM_CONFIG_MAX_VALUE_INIT_VALUE;
    }
}

uint16_t rgbProgramConfigGetDelay(rgb_section_t section)
{
    if(section >= rgbNumberOfSections)
        return 0;

    return rgbProgramConfig[section].delay;
}

color_value_t rgbProgramConfigGetMaxValue(rgb_section_t section)
{
    if(section >= rgbNumberOfSections)
        return 0;

    return rgbProgramConfig[section].maxValue;
}

void rgbProgramConfigSet(rgb_program_configuration_t *tempConfig)
{
    for(uint8_t i = 0; i < rgbNumberOfSections; i++)
    {
        memcpy(rgbProgramConfig + i, tempConfig + i, sizeof(rgb_program_configuration_t));
    }

    configChanged = true;
}

void rgbProgramConfigGet(rgb_program_configuration_t *tempConfig)
{
    for(uint8_t i = 0; i < rgbNumberOfSections; i++)
    {
        memcpy(tempConfig + i, rgbProgramConfig + i, sizeof(rgb_program_configuration_t));
    }
}