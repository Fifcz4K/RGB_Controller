#include "models.h"
#include "server_http.h"
#include "outputs.h"
#include "device_task_handler.h"
#include "f_eeprom.h"
#include "wifi_handler.h"
#include "f_adc.h"
#include "measurements.h"

static const char *TAG = "MAIN.C";

void app_main(void)
{
    eepromInit();
    deviceConfigInit();
    rgbProgramsConfigInit();
    outputs_init();
    adcInit();
    wifiInit();
    startServerHttp();
    measurementProcess(measureLight, adcGetValue(adcLightChannel));

    while(1)
    {
        measurementProcess(measureTemperature, adcGetValue(adcTemperatureChannel));
        DELAY(100);
        if(isConfigChanged() == true)
        {
            rgbTasksController();
        }

        if(isWifiChanged() == true)
        {
            eepromSave(wifiGetCredentials(), sizeof(wifi_t), "wifi");
        }
    }
}