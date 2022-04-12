#include "rgb_programs.h"

static void rgbProgramZero(rgb_section_t section);
static void rgbProgramOne(rgb_section_t section);

rgb_programs_callbacks_t rgbProgramsCallback[rgbNumberOfPrograms] =
{
    {rgbProgram0, rgbProgramZero},
    {rgbProgram1, rgbProgramOne}
};

void (*rgbGetProgramFunction(rgb_program_number_t program))(rgb_section_t section)
{
    for(uint8_t i = 0; i < rgbNumberOfPrograms; i++)
    {
        if(rgbProgramsCallback[i].program == program)
        {
            return rgbProgramsCallback[i].callback;
        }
    }

    return NULL;
}

static void setPWM(rgb_section_t section, color_value_t red, color_value_t green, color_value_t blue)
{
    switch(section)
    {
        case rgbSectionOne:
            outputs_setPWM(RGB_OUTPUT_RED_1, red);
            outputs_setPWM(RGB_OUTPUT_GREEN_1, green);
            outputs_setPWM(RGB_OUTPUT_BLUE_1, blue);
        break;

        case rgbSectionTwo:
            outputs_setPWM(RGB_OUTPUT_RED_2, red);
            outputs_setPWM(RGB_OUTPUT_GREEN_2, green);
            outputs_setPWM(RGB_OUTPUT_BLUE_2, blue);
        break;
        
        default:
        break;
    }
}

static void rgbProgramZero(rgb_section_t section)
{
    setPWM(section, deviceConfigGetColor(section, Red), deviceConfigGetColor(section, Green), deviceConfigGetColor(section, Blue));
}

static void rgbProgramOne(rgb_section_t section)
{
    static color_value_t colorValue = 0;
    static bool colorUp = true;
    static color_t colorToChange = Red;

    if(colorUp)
    {
        colorValue++;
        if(colorValue == rgbProgramConfigGetMaxValue(section))
        {
            colorUp = false;
        }
    }
    else
    {
        colorValue--;
        if(colorValue == 0)
        {
            colorUp = true;
            colorToChange++;
            if(colorToChange >= NumberOfColors)
                colorToChange = Red;
        }
    }

    switch(colorToChange)
    {
        case Red:
            setPWM(section, colorValue, 0, 0);
        break;

        case Green:
            setPWM(section, 0, colorValue, 0);
        break;

        case Blue:
            setPWM(section, 0, 0, colorValue);
        break;

        default:
        break;
    }
}

static void rgbProgramTwo(rgb_section_t section)
{
    //program 1, mixing colors
}


static void rgbProgramThree(rgb_section_t section)
{
    //randomize colors
}





