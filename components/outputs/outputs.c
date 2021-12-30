#include "outputs.h"

static const char *TAG = "OUTPUTS.C";

void outputs_init(void)
{
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_RGB_TRANSISTORS_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;

    gpio_config(&io_conf);
}