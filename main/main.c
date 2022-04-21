
#include "server_http.h"
#include "outputs.h"
#include "device_task_handler.h"
#include "f_eeprom.h"
#include "wifi_handler.h"
#include "measurements.h"

static const char *TAG = "MAIN.C";

static void wifiInit(void);

void app_main(void)
{
    eepromInit();
    outputs_init();
    adcInit();
    taskHandlerMeasurements();
    wifiInit();
    startServerHttp();

    while(1)
    {
        DELAY(20);
        // if(isConfigChanged() == true)
        // {
        //     taskHandlerRGB();
        // }

        if(isWifiChanged() == true)
        {
            eepromSave(wifiGetCredentials(), sizeof(wifi_t), "wifi");
        }
    }
}

static void wifiInit(void)
{
    wifi_workmode_t wifiMode;
    if(eepromRead(wifiGetCredentials(), sizeof(wifi_t), "wifi") == true)
    {
        wifiMode = WifiStation;
    }
    else
    {
        wifiMode = WifiAccessPoint;
    }

    wifiStart(wifiMode);
}