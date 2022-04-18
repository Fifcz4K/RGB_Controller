#include "models.h"
#include "server_http.h"
#include "outputs.h"
#include "device_task_handler.h"
#include "f_eeprom.h"
#include "wifi_handler.h"
#include "measurements.h"

static const char *TAG = "MAIN.C";

void app_main(void)
{
    eepromInit();
    deviceConfigInit();
    rgbProgramsConfigInit();
    outputs_init();
    adcInit();
    taskHandlerMeasurements();
    wifiInit();
    startServerHttp();

    while(1)
    {
        DELAY(20);
        if(isConfigChanged() == true)
        {
            taskHandlerRGB();
        }

        if(isWifiChanged() == true)
        {
            eepromSave(wifiGetCredentials(), sizeof(wifi_t), "wifi");
        }
    }
}