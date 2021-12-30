#include <nvs_flash.h>
#include "nvs_flash.h"
#include "protocol_examples_common.h"

#include "common.h"
#include "models.h"
#include "server_http.h"
#include "outputs.h"

static const char *TAG = "MAIN.C";

static void systemInit(void);

static void blink(void)
{
    uint16_t counter = 0;
    while(1)
    {
        vTaskDelay(1000 / portTICK_RATE_MS);
        gpio_set_level(GPIO_R1, counter++ % 2);   
    }
}

void app_main(void)
{
    systemInit();
    startServerHttp();
    outputs_init();
    xTaskCreate(blink, "blink", 4096, NULL, 3, NULL);
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