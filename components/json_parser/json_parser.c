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

static void jsonParseRgbProgram(cJSON* jsonInput, rgb_program_configuration_t* config, const char* objectName)
{
    cJSON* jsonConfig = cJSON_GetObjectItem(jsonInput, objectName);

    if(cJSON_HasObjectItem(jsonConfig, "Del"))
        config->delay = cJSON_GetObjectItem(jsonConfig, "Del")->valueint;

    if(cJSON_HasObjectItem(jsonConfig, "Max"))
        config->maxValue = cJSON_GetObjectItem(jsonConfig, "Max")->valueint;
}

jsonParse_t jsonParseSetRgbProgramConfiguration(const char* jsonInput)
{
    rgb_program_configuration_t tempConfig[rgbNumberOfSections];
    rgbProgramConfigGet(tempConfig);

    cJSON* jsonRoot = cJSON_Parse(jsonInput);

    if(cJSON_HasObjectItem(jsonRoot, "S1"))
    {
        jsonParseRgbProgram(jsonRoot, &tempConfig[rgbSectionOne], "S1");
    }

    if(cJSON_HasObjectItem(jsonRoot, "S2"))
    {
        jsonParseRgbProgram(jsonRoot, &tempConfig[rgbSectionTwo], "S2");
    }

    rgbProgramConfigSet(tempConfig);

    return jsonParseOk;
}

jsonParse_t jsonParseWifi(const char* jsonInput)
{
    wifi_t wifi;
    memset(&wifi, 0, sizeof(wifi_t));

    cJSON *jsonRoot = cJSON_Parse(jsonInput);

    if(cJSON_HasObjectItem(jsonRoot, "ssid"))
    {
        strcpy(&wifi.ssid, cJSON_GetObjectItem(jsonRoot, "ssid")->valuestring);
    }
    else
    {
        return jsonParseErr;
    }

    if(cJSON_HasObjectItem(jsonRoot, "pass"))
    {
        strcpy(&wifi.password, cJSON_GetObjectItem(jsonRoot, "pass")->valuestring);
    }
    else
    {
        return jsonParseErr;
    }

    wifiSetCredentials(&wifi);
    
    return jsonParseOk;
}




