#ifndef _DEVICE_CONFIG_H_
#define _DEVICE_CONFIG_H_

#include "models.h"
#include "common.h"

#define PROGRAM_CONFIG_DELAY_INIT_VALUE 10
#define PROGRAM_CONFIG_MAX_VALUE_INIT_VALUE 255

bool isConfigChanged(void);
void deviceConfigInit(void);
bool deviceConfigSetRGB(rgb_section_t section, color_value_t red, color_value_t green, color_value_t blue);
bool deviceConfigSetLightSensor(light_sensor_t value);
bool deviceConfigSetProgram(rgb_section_t section, rgb_program_number_t program);
light_sensor_t deviceConfigGetLightSensor(void);
color_value_t deviceConfigGetColor(rgb_section_t section, color_t color);
rgb_program_number_t deviceConfigGetProgram(rgb_section_t section);
bool deviceConfigSet(device_configuration_t *tempConfig);
void deviceConfigGet(device_configuration_t *tempConfig);
void rgbProgramsConfigInit(void);
uint16_t rgbProgramConfigGetDelay(rgb_section_t section);
color_value_t rgbProgramConfigGetMaxValue(rgb_section_t section);
void rgbProgramConfigSet(rgb_program_configuration_t *tempConfig);
void rgbProgramConfigGet(rgb_program_configuration_t *tempConfig);

#endif