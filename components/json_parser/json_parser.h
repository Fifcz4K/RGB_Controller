#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "cJSON.h"
#include "common.h"
#include "wifi_credentials.h"
#include "rgb_configuration.h"

typedef enum
{
    jsonParseOk,
    jsonParseErr,
}jsonParse_t;

jsonParse_t jsonParseWifi(const char* jsonInput);
jsonParse_t jsonParseRgbConfig(const char* jsonInput);

#endif // JSON_PARSER_H