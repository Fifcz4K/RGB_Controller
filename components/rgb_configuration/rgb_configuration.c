#include "rgb_configuration.h"

static rgb_configuration_t rgbConfiguration[rgbNumberOfSections][NumberOfColors];
static uint16_t rgbDelays[rgbNumberOfSections][NumberOfColors] = 
{
    {0, 0, 0},
    {0, 0, 0}
};

void rgbInit(void)
{
    for(uint8_t i = 0; i < rgbNumberOfSections; i++)
    {
        for(uint8_t j = 0; j < NumberOfColors; j++)
        {
            rgbConfiguration[i][j].value = 0;
            rgbConfiguration[i][j].step = 1;
            rgbConfiguration[i][j].minValue = 0;
            rgbConfiguration[i][j].maxValue = 255;
            rgbConfiguration[i][j].direction = rgbIncrementing;
            rgbConfiguration[i][j].delay = 0;
        }
    }
}

void rgbGetConfig(rgb_configuration_t *config)
{
    memcpy(config, &rgbConfiguration, sizeof(rgb_configuration_t) * (rgbNumberOfSections * NumberOfColors));
}

/*
static void printConfig(void)
{
    for(uint8_t i = 0; i < rgbNumberOfSections; i++)
    {
        for(uint8_t j = 0; j < NumberOfColors; j++)
        {
            printf("value: %d, step: %d, min: %d, max: %d, direction: %d, delay: %d\n", \
            rgbConfiguration[i][j].value, rgbConfiguration[i][j].step, \
            rgbConfiguration[i][j].minValue, rgbConfiguration[i][j].maxValue, \
            rgbConfiguration[i][j].direction, rgbConfiguration[i][j].delay);
        }
    }
}
*/

void rgbSetConfig(rgb_configuration_t *config)
{
    memcpy(&rgbConfiguration, config, sizeof(rgb_configuration_t) * (rgbNumberOfSections * NumberOfColors));
}

color_value_t rgbGetColorValue(rgb_section_t section, color_t color)
{
    if(rgbConfiguration[section][color].delay > 0)
    {
        rgbDelays[section][color] += 10;
        if(rgbDelays[section][color] >= rgbConfiguration[section][color].delay)
        {
            rgbDelays[section][color] = 0;

            if(rgbConfiguration[section][color].direction == rgbIncrementing)
            {
                if(rgbConfiguration[section][color].value + rgbConfiguration[section][color].step > rgbConfiguration[section][color].maxValue)
                {
                    rgbConfiguration[section][color].direction = rgbDecrementing;
                }
                else
                {
                    rgbConfiguration[section][color].value += rgbConfiguration[section][color].step;                    
                }
            }
            else
            {
                if(rgbConfiguration[section][color].value - rgbConfiguration[section][color].step < rgbConfiguration[section][color].minValue)
                {
                    rgbConfiguration[section][color].direction = rgbIncrementing;
                }
                else
                {
                    rgbConfiguration[section][color].value -= rgbConfiguration[section][color].step;                    
                }
            }

            if(rgbConfiguration[section][color].value >= rgbConfiguration[section][color].maxValue)
            {
                rgbConfiguration[section][color].value = rgbConfiguration[section][color].maxValue;
                rgbConfiguration[section][color].direction = 1 - rgbConfiguration[section][color].direction;
            }

            if(rgbConfiguration[section][color].value <= rgbConfiguration[section][color].minValue)
            {
                rgbConfiguration[section][color].value = rgbConfiguration[section][color].minValue;
                rgbConfiguration[section][color].direction = 1 - rgbConfiguration[section][color].direction;
            }
        }
    }

    return rgbConfiguration[section][color].value;
}