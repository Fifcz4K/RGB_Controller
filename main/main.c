#include <nvs_flash.h>
#include "protocol_examples_common.h"

#include "models.h"
#include "server_http.h"
#include "outputs.h"
#include "device_task_handler.h"
#include "f_eeprom.h"
#include "wifi_handler.h"

static const char *TAG = "MAIN.C";

void app_main(void)
{
    eepromInit();
    deviceConfigInit();
    rgbProgramsConfigInit();
    outputs_init();
    // systemInit();
    wifiInit();
    startServerHttp();

    while(1)
    {
        DELAY(10);
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