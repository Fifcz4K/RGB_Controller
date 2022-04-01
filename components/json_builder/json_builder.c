#include "json_builder.h"

static const char *TAG = "JSON_BUILDER.C";

static void jsonBuildRGB(cJSON *jsonConfig, const char *objectName, rgb_t *rgb)
{
    cJSON *jsonRGB = cJSON_CreateObject();

    cJSON_AddNumberToObject(jsonRGB, "R", rgb->color[Red]);
    cJSON_AddNumberToObject(jsonRGB, "G", rgb->color[Green]);
    cJSON_AddNumberToObject(jsonRGB, "B", rgb->color[Blue]);

    cJSON_AddItemToObject(jsonConfig, objectName, jsonRGB);
}

cJSON* jsonBuildConfiguration(void)
{
    device_configuration_t tempConfig;
    deviceConfigGet(&tempConfig);

    cJSON *jsonConfig = cJSON_CreateObject();

    jsonBuildRGB(jsonConfig, "RGB1", &tempConfig.rgb[rgbSectionOne]);
    jsonBuildRGB(jsonConfig, "RGB2", &tempConfig.rgb[rgbSectionTwo]);

    cJSON_AddBoolToObject(jsonConfig, "LiSen", tempConfig.lightSensor);
    cJSON_AddNumberToObject(jsonConfig, "Prog", tempConfig.program);

    return jsonConfig;
}

cJSON* jsonBuildMeasurements(void)
{
    cJSON *jsonMeasurements = cJSON_CreateObject();

    // cJSON_AddBoolToObject(jsonMeasurements, "LiSen", tempConfig.lightSensor);
    // cJSON_AddNumberToObject(jsonMeasurements, "Prog", tempConfig.program);

    return jsonMeasurements;
}


