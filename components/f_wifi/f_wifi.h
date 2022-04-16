#ifndef _WIFI_H_
#define _WIFI_H_

#include "esp_wifi.h"
#include "nvs_flash.h"

#include "common.h"
#include "f_eeprom.h"

#define WIFI_ACCESS_POINT_SSID          "RGB_CONTROLLER_AP"
#define WIFI_ACCESS_POINT_PASSWORD      "RGB-ACCESS-132"
#define WIFI_ACCESS_POINT_CHANNEL       1
#define WIFI_ACCESS_POINT_MAX_STATION   1

typedef struct
{
    char ssid[30];
    char password[30];
}wifi_t;

typedef  enum
{
    WifiStation,
    WifiAccessPoint
}wifi_workmode_t;

bool isWifiChanged(void);
void wifiSetCredentials(wifi_t *newWifi);
wifi_t* wifiGetCredentials(void);
char* wifiGetSsid(void);
char* wifiGetPassword(void);
void wifiInit(void);


#endif