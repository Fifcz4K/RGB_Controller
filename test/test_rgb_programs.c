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

void test_rgb_program_1(void)
{
    outputs_setPWM_Expect(RGB_OUTPUT_RED_1, 0);
    outputs_setPWM_Expect(RGB_OUTPUT_GREEN_1, 0);
    outputs_setPWM_Expect(RGB_OUTPUT_BLUE_1, 0);

    outputs_setPWM_Expect(RGB_OUTPUT_RED_2, 0);
    outputs_setPWM_Expect(RGB_OUTPUT_GREEN_2, 0);
    outputs_setPWM_Expect(RGB_OUTPUT_BLUE_2, 0);

    void (*programFunction)(void);
    programFunction = rgbGetProgramFunction(rgbProgram0);
    programFunction();
}
