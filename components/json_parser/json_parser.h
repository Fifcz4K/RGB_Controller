#ifndef _JSON_PARSER_H_
#define _JSON_PARSER_H_

#include "common.h"
#include "models.h"

typedef enum
{
    jsonParseOk,
    jsonParseErr,
}jsonParse_t;

jsonParse_t jsonParseSetDevice(const char* jsonInput, control_t* control);

#endif