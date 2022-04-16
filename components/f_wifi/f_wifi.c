#include "f_wifi.h"

static const char *TAG = "WIFI.C";

static wifi_t wifiCredentials = {0};
static wifi_workmode_t wifiMode;

bool wifiChanged = false;

bool isWifiChanged(void)
{
    bool retVal = false;

    if(wifiChanged == true)
    {
        retVal = true;
        wifiChanged = false;
    }

    return retVal;
}

void wifiSetCredentials(wifi_t *newWifi)
{
    memcpy(&wifiCredentials, newWifi, sizeof(wifi_t));
    wifiChanged = true;
}

wifi_t* wifiGetCredentials(void)
{
    return &wifiCredentials;
}

char* wifiGetSsid(void)
{
    return wifiCredentials.ssid;
}

char* wifiGetPassword(void)
{
    return wifiCredentials.password;
}


static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}

static void wifi_init_softap(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = WIFI_ACCESS_POINT_SSID,
            .ssid_len = strlen(WIFI_ACCESS_POINT_SSID),
            .channel = WIFI_ACCESS_POINT_CHANNEL,
            .password = WIFI_ACCESS_POINT_PASSWORD,
            .max_connection = WIFI_ACCESS_POINT_MAX_STATION,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
    if (strlen(WIFI_ACCESS_POINT_PASSWORD) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             WIFI_ACCESS_POINT_SSID, WIFI_ACCESS_POINT_PASSWORD, WIFI_ACCESS_POINT_CHANNEL);
}

void wifiInit(void)
{
    if(eepromRead(&wifiCredentials, sizeof(wifi_t), "wifi") == true)
    {
        wifiMode = WifiStation;
    }
    else
    {
        wifiMode = WifiAccessPoint;
    }

    switch(wifiMode)
    {
        case WifiStation:

        break;

        case WifiAccessPoint:
            wifi_init_softap();
        break;

        default:
        break;
    }
}















