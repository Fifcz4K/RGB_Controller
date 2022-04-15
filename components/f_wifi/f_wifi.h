#ifndef _WIFI_H_
#define _WIFI_H_

#include "common.h"

typedef struct
{
    char ssid[30];
    char password[30];
}wifi_t;

bool isWifiChanged(void);
void wifiSetCredentials(wifi_t *newWifi);
wifi_t* wifiGetCredentials(void);
char* wifiGetSsid(void);
char* wifiGetPassword(void);


#endif