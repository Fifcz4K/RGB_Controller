#include "f_wifi.h"

static const char *TAG = "WIFI.C";

static wifi_t wifiCredentials = {0};

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
