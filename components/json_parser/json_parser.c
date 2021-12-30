#include "json_parser.h"

static const char *TAG = "JSON_PARSER.C";

static jsonParse_t jsonParseRGB(cJSON* jsonInput, rgb_t* rgb, const char* objectName)
{
    cJSON* jsonRGB = cJSON_GetObjectItem(jsonInput, objectName);
    rgb->red = cJSON_GetObjectItem(jsonRGB, "R")->valueint;
    rgb->green = cJSON_GetObjectItem(jsonRGB, "G")->valueint;
    rgb->blue = cJSON_GetObjectItem(jsonRGB, "B")->valueint;

    return jsonParseOk;
}

jsonParse_t jsonParseSetDevice(const char* input, control_t* control) 
{
    cJSON* jsonRoot = cJSON_Parse(input);

    jsonParseRGB(jsonRoot, &control->rgbOne, "RGB1");
    jsonParseRGB(jsonRoot, &control->rgbTwo, "RGB2");

    control->lightSensor = cJSON_GetObjectItem(jsonRoot, "LiSen")->valueint;

    return jsonParseOk;
}