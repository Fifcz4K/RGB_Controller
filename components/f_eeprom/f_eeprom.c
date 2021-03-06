#include "f_eeprom.h"

static const char *TAG = "EEPROM.c";

bool eepromInit(void)
{
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 2,
      .format_if_mount_failed = true
    };

    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return false;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    return true;
}

bool eepromSave(uint8_t *data, uint16_t dataLen, char* fileName)
{
    char filePath[50] = {0};
    sprintf(filePath, "/spiffs/%s.txt", fileName);
    ESP_LOGI(TAG, "Opening file %s", filePath);
    FILE* f = fopen("/spiffs/wifi.txt", "wb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return false;
    }
    fwrite(data, 1, dataLen, f);
    fclose(f);
    ESP_LOGI(TAG, "File written");

    return true;
}

bool eepromRead(uint8_t *data, uint16_t dataLen, char* fileName)
{
    char filePath[50] = {0};
    sprintf(filePath, "/spiffs/%s.txt", fileName);
    ESP_LOGI(TAG, "Reading file %s", filePath);
    FILE* f = fopen("/spiffs/wifi.txt", "rb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return false;
    }
    fread(data, 1, dataLen, f);
    fclose(f);
    ESP_LOGI(TAG, "Reading finished");

    return true;
}

void eepromDelete(char* fileName)
{
    char filePath[50] = {0};
    sprintf(filePath, "/spiffs/%s.txt", fileName);

    unlink(filePath);
}