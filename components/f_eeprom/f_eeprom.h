#ifndef _F_EEPROM_H_
#define _F_EEPROM_H_

#include "esp_spiffs.h"
#include <sys/unistd.h>
#include <esp_log.h>

#include "common.h"

bool eepromInit(void);
bool eepromSave(uint8_t *data, uint16_t dataLen, char* fileName);
bool eepromRead(uint8_t *data, uint16_t dataLen, char* fileName);
void eepromDelete(char* fileName);

#endif