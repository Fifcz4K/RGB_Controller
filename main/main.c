
#include "server_http.h"
#include "outputs.h"
#include "device_task_handler.h"
#include "f_eeprom.h"
#include "wifi_handler.h"
#include "measurements.h"

static void wifiInit(void);

void app_main(void)
{
    eepromInit();
    outputs_init();
    adcInit();
    wifiInit();
    startServerHttp();
    taskHandlerMeasurements();
    taskHandlerRGB();

    while(1)
    {
        DELAY(10);

        if(isWifiChanged() == true)
        {
            eepromSave((uint8_t*)wifiGetCredentials(), sizeof(wifi_t), "wifi");
        }
    }
}

static void wifiInit(void)
{
    wifi_workmode_t wifiMode;
    if(eepromRead((uint8_t*)wifiGetCredentials(), sizeof(wifi_t), "wifi") == true)
    {
        wifiMode = WifiStation;
    }
    else
    {
        wifiMode = WifiAccessPoint;
    }

    wifiStart(wifiMode);
}