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

color_value_t rgbGetColorValue(rgb_section_t section, color_t color)
{
    if(rgbConfiguration[section][color].delay > 0)
    {
        rgbDelays[section][color]++;
        if(rgbDelays[section][color] >= rgbConfiguration[section][color].delay)
        {
            rgbDelays[section][color] = 0;

            if(rgbConfiguration[section][color].direction == rgbIncrementing)
            {
                rgbConfiguration[section][color].value += rgbConfiguration[section][color].step;
            }
            else
            {
                rgbConfiguration[section][color].value += rgbConfiguration[section][color].step;
            }

            if(rgbConfiguration[section][color].value > rgbConfiguration[section][color].maxValue)
            {
                rgbConfiguration[section][color].value = rgbConfiguration[section][color].maxValue;
            }

            if(rgbConfiguration[section][color].value < rgbConfiguration[section][color].minValue)
            {
                rgbConfiguration[section][color].value = rgbConfiguration[section][color].minValue;
            }
        }
    }


    return rgbConfiguration[section][color].value;
}