#include "json_parser.h"

static const char *TAG = "JSON_PARSER.C";

static void jsonParseRGB(cJSON* jsonInput, rgb_t* rgb, const char* objectName)
{
    cJSON* jsonRGB = cJSON_GetObjectItem(jsonInput, objectName);

    if(cJSON_HasObjectItem(jsonRGB, "R"))
        rgb->color[Red] = cJSON_GetObjectItem(jsonRGB, "R")->valueint;

    if(cJSON_HasObjectItem(jsonRGB, "G"))
        rgb->color[Green] = cJSON_GetObjectItem(jsonRGB, "G")->valueint;

    if(cJSON_HasObjectItem(jsonRGB, "B"))
        rgb->color[Blue] = cJSON_GetObjectItem(jsonRGB, "B")->valueint;

    if(cJSON_HasObjectItem(jsonRGB, "Prog"))
    {
        rgb->program = cJSON_GetObjectItem(jsonRGB, "Prog")->valueint;
    }
}

jsonParse_t jsonParseSetConfiguration(const char* jsonInput)
{
    device_configuration_t tempConfig;
    deviceConfigGet(&tempConfig);
    cJSON* jsonRoot = cJSON_Parse(jsonInput);

    if(cJSON_HasObjectItem(jsonRoot, "RGB1"))
    {
        jsonParseRGB(jsonRoot, &tempConfig.rgb[rgbSectionOne], "RGB1");
    }

    if(cJSON_HasObjectItem(jsonRoot, "RGB2"))
    {
        jsonParseRGB(jsonRoot, &tempConfig.rgb[rgbSectionTwo], "RGB2");
    }

    if(cJSON_HasObjectItem(jsonRoot, "LiSen"))
    {
        tempConfig.lightSensor = cJSON_GetObjectItem(jsonRoot, "LiSen")->valueint;
    }

    if(deviceConfigSet(&tempConfig) == false)
        return jsonParseErr;

    return jsonParseOk;
}