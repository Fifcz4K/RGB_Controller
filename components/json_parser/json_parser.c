#include "json_parser.h"

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

static void jsonParseColorConfig(cJSON* jsonInput, rgb_configuration_t *item, const char* objectName)
{
    cJSON* jsonColorConfig = cJSON_GetObjectItem(jsonInput, objectName);

    if(cJSON_HasObjectItem(jsonColorConfig, "v"))
    {
        item->value = cJSON_GetObjectItem(jsonColorConfig, "v")->valueint;
    }

    if(cJSON_HasObjectItem(jsonColorConfig, "s"))
    {
        item->step = cJSON_GetObjectItem(jsonColorConfig, "s")->valueint;
    }

    if(cJSON_HasObjectItem(jsonColorConfig, "m"))
    {
        item->minValue = cJSON_GetObjectItem(jsonColorConfig, "m")->valueint;
    }

    if(cJSON_HasObjectItem(jsonColorConfig, "ma"))
    {
        item->maxValue = cJSON_GetObjectItem(jsonColorConfig, "ma")->valueint;
    }

    if(cJSON_HasObjectItem(jsonColorConfig, "d"))
    {
        item->direction = cJSON_GetObjectItem(jsonColorConfig, "d")->valueint;
    }

    if(cJSON_HasObjectItem(jsonColorConfig, "de"))
    {
        item->delay = cJSON_GetObjectItem(jsonColorConfig, "de")->valueint;
    }
}

const char* colorLUT[rgbNumberOfSections][NumberOfColors] =
{
    {"R1", "G1", "B1"},
    {"R2", "G2", "B2"}
};

jsonParse_t jsonParseRgbConfig(const char* jsonInput)
{
    rgb_configuration_t tempConfig[rgbNumberOfSections][NumberOfColors];
    rgbGetConfig(tempConfig);

    cJSON* jsonRoot = cJSON_Parse(jsonInput);

    for(uint8_t i = 0; i < rgbNumberOfSections; i++)
    {
        for(uint8_t j = 0; j < NumberOfColors; j++)
        {
            if(cJSON_HasObjectItem(jsonRoot, colorLUT[i][j]))
            {
                jsonParseColorConfig(jsonRoot, &tempConfig[i][j], colorLUT[i][j]);
            }
        }
    }

    rgbSetConfig(tempConfig);

    return jsonParseOk;
}