#ifndef _JSON_PARSER_H_
#define _JSON_PARSER_H_

#include "cJSON.h"
#include "models.h"
#include "common.h"
#include "device_config.h"

typedef enum
{
    jsonParseOk,
    jsonParseErr,
}jsonParse_t;

jsonParse_t jsonParseSetConfiguration(const char* jsonInput);
jsonParse_t jsonParseSetRgbProgramConfiguration(const char* jsonInput);

#endif