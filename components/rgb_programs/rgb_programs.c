#include "rgb_programs.h"

static const char *TAG = "RGB_PROGRAM.C";

static void rgbProgramZero(void);
static void rgbProgramOne(void);

rgb_programs_callbacks_t rgbProgramsCallback[rgbNumberOfPrograms] =
{
    {rgbProgram0, rgbProgramZero},
    {rgbProgram1, rgbProgramOne}
};

void (*rgbGetProgramFunction(rgb_program_number_t program))()
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

static void rgbProgramZero(void)
{
    outputs_setPWM(RGB_OUTPUT_RED_1, deviceConfigGetColor(rgbSectionOne, Red));
    outputs_setPWM(RGB_OUTPUT_GREEN_1, deviceConfigGetColor(rgbSectionOne, Green));
    outputs_setPWM(RGB_OUTPUT_BLUE_1, deviceConfigGetColor(rgbSectionOne, Blue));

    outputs_setPWM(RGB_OUTPUT_RED_2, deviceConfigGetColor(rgbSectionTwo, Red));
    outputs_setPWM(RGB_OUTPUT_GREEN_2, deviceConfigGetColor(rgbSectionTwo, Green));
    outputs_setPWM(RGB_OUTPUT_BLUE_2, deviceConfigGetColor(rgbSectionTwo, Blue));
}

static void rgbProgramOne(void)
{
    static color_value_t r1 = 0, g1 = 0, b1 = 0;
    static color_value_t r2 = 0, g2 = 0, b2 = 0;
    bool redUp = true;
    if(redUp)
    {
        r1++;
        if(r1 == 255)
            redUp = false;
    }
    else
    {
        r1--;
        if(r1 == 0)
        {
            redUp = true;
        }
    }

    outputs_setPWM(RGB_OUTPUT_RED_1, r1);
}






