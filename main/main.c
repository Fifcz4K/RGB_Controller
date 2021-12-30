#include <nvs_flash.h>
#include "nvs_flash.h"
#include "protocol_examples_common.h"

#include "common.h"
#include "models.h"
#include "server_http.h"

static const char *TAG = "MAIN.C";

static void systemInit(void);

void app_main(void)
{
    systemInit();
    startServerHttp();
}

static void systemInit(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());
}