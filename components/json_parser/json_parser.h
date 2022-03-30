#ifndef _JSON_PARSER_H_
#define _JSON_PARSER_H_

#include "cJSON.h"
#include "models.h"

typedef enum
{
    jsonParseOk,
    jsonParseErr,
}jsonParse_t;

jsonParse_t jsonParseSetDevice(const char* jsonInput, device_configuration_t* control);

#endif