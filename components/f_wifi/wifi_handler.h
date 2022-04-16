#ifndef _WIFI_HANDLER_H_
#define _WIFI_HANDLER_H_

#include "esp_wifi.h"
#include "nvs_flash.h"
#include "freertos/event_groups.h"

#include "wifi_credentials.h"
#include "f_eeprom.h"

#define WIFI_ACCESS_POINT_SSID          "RGB_CONTROLLER_AP"
#define WIFI_ACCESS_POINT_PASSWORD      "RGB-ACCESS-132"
#define WIFI_ACCESS_POINT_CHANNEL       1
#define WIFI_ACCESS_POINT_MAX_STATION   1

#define WIFI_STATION_MAXIMUM_RETRY  5

void wifiInit(void);

#endif