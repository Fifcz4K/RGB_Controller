#include "json_parser.h"

static const char *TAG = "JSON_PARSER.C";

static jsonParse_t jsonParseRGB(cJSON* jsonInput, rgb_t* rgb, const char* objectName)
{
    cJSON* jsonRGB = cJSON_GetObjectItem(jsonInput, objectName);
    if(cJSON_HasObjectItem(jsonRGB, "R"))
        rgb->color[Red] = cJSON_GetObjectItem(jsonRGB, "R")->valueint;
    else
        return jsonParseErr;

    if(cJSON_HasObjectItem(jsonRGB, "G"))
        rgb->color[Green] = cJSON_GetObjectItem(jsonRGB, "G")->valueint;
    else
        return jsonParseErr;

    if(cJSON_HasObjectItem(jsonRGB, "B"))
        rgb->color[Blue] = cJSON_GetObjectItem(jsonRGB, "B")->valueint;
    else
        return jsonParseErr;

    return jsonParseOk;
}

jsonParse_t jsonParseSetConfiguration(const char* jsonInput)
{
    device_configuration_t tempConfig;
    cJSON* jsonRoot = cJSON_Parse(jsonInput);
    // printf("%s\n:", cJSON_Print(jsonRoot));

    if(cJSON_HasObjectItem(jsonRoot, "RGB1"))
    {
        jsonParseRGB(jsonRoot, &tempConfig.rgb[rgbSectionOne], "RGB1");
    }

    if(cJSON_HasObjectItem(jsonRoot, "RGB2"))
    {
        jsonParseRGB(jsonRoot, &tempConfig.rgb[rgbSectionTwo], "RGB2");
    }

    tempConfig.program = cJSON_GetObjectItem(jsonRoot, "Prog")->valueint;
    if(cJSON_GetObjectItem(jsonRoot, "LiSen")->valueint == 0)
        tempConfig.lightSensor = lightSensorOff;
    else
        tempConfig.lightSensor = lightSensorOn;

    return jsonParseOk;
}