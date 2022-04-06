#ifndef _RGB_PROGRAM_H_
#define _RGB_PROGRAM_H_

#include "models.h"
#include "common.h"
#include "device_config.h"
#include "outputs.h"

// typedef struct
// {
//     bool runProgram;
//     uint16_t delay;

// }rgb_program_t;

typedef struct
{
    rgb_program_number_t program;
    void (*callback)(void);
}rgb_programs_callbacks_t;

void (*rgbGetProgramFunction(rgb_program_number_t program))();

#endif