#ifndef _RGB_PROGRAM_H_
#define _RGB_PROGRAM_H_

#include "models.h"
#include "common.h"
#include "device_config.h"
#include "outputs.h"

typedef struct
{
    rgb_program_number_t program;
    void (*callback)(void);
}rgb_programs_callbacks_t;

void (*rgbGetProgramFunction(rgb_program_number_t program))(rgb_section_t section);

#endif