#include "unity.h"

#include "rgb_programs.h"
#include "device_config.h"
#include "mock_outputs.h"

void setUp(void)
{
    deviceConfigInit();
}

void tearDown(void)
{
    
}

void test_rgb_program_0_section_1(void)
{
    outputs_setPWM_Expect(RGB_OUTPUT_RED_1, 0);
    outputs_setPWM_Expect(RGB_OUTPUT_GREEN_1, 0);
    outputs_setPWM_Expect(RGB_OUTPUT_BLUE_1, 0);

    void (*programFunction)(rgb_section_t section);
    programFunction = rgbGetProgramFunction(rgbProgram0);
    programFunction(rgbSectionOne);
}

void test_rgb_program_0_section_2(void)
{
    outputs_setPWM_Expect(RGB_OUTPUT_RED_2, 0);
    outputs_setPWM_Expect(RGB_OUTPUT_GREEN_2, 0);
    outputs_setPWM_Expect(RGB_OUTPUT_BLUE_2, 0);

    void (*programFunction)(rgb_section_t section);
    programFunction = rgbGetProgramFunction(rgbProgram0);
    programFunction(rgbSectionTwo);
}

void test_rgb_program_0_section_both(void)
{
    color_value_t r1 = 100, g1 = 200, b1 = 255;
    color_value_t r2 = 25, g2 = 0, b2 = 33;

    outputs_setPWM_Expect(RGB_OUTPUT_RED_1, r1);
    outputs_setPWM_Expect(RGB_OUTPUT_GREEN_1, g1);
    outputs_setPWM_Expect(RGB_OUTPUT_BLUE_1, b1);

    outputs_setPWM_Expect(RGB_OUTPUT_RED_2, r2);
    outputs_setPWM_Expect(RGB_OUTPUT_GREEN_2, g2);
    outputs_setPWM_Expect(RGB_OUTPUT_BLUE_2, b2);

    deviceConfigSetRGB(rgbSectionOne, r1, g1, b1);
    deviceConfigSetRGB(rgbSectionTwo, r2, g2, b2);

    void (*programSectionOne)(rgb_section_t section);
    void (*programSectionTwo)(rgb_section_t section);

    programSectionOne = rgbGetProgramFunction(rgbProgram0);
    programSectionTwo = rgbGetProgramFunction(rgbProgram0);

    programSectionOne(rgbSectionOne);
    programSectionTwo(rgbSectionTwo);
}





