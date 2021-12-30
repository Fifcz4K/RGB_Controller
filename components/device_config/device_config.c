#include "device_config.h"

static const char *TAG = "DEVICE_CONFIG.C";

control_t deviceConfig;

control_t* getDeviceConfig()
{
    return &deviceConfig;
}

void printDeviceConfig()
{
    ESP_LOGI(TAG, "RGB1");
    ESP_LOGI(TAG, "R: %d G: %d B: %d", deviceConfig.rgbOne.red, deviceConfig.rgbOne.green, deviceConfig.rgbOne.blue);
    ESP_LOGI(TAG, "RGB2");
    ESP_LOGI(TAG, "R: %d G: %d B: %d", deviceConfig.rgbTwo.red, deviceConfig.rgbTwo.green, deviceConfig.rgbTwo.blue);
    ESP_LOGI(TAG, "Light Sensor: %d\n", deviceConfig.lightSensor);
}