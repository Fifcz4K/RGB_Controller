#include "outputs.h"

static const char *TAG = "OUTPUTS.C";

ledc_channel_config_t ledc_channel[LEDC_TEST_CH_NUM] = 
{
    {
        .channel    = LEDC_LS_CH0_CHANNEL,
        .duty       = 0,
        .gpio_num   = LEDC_LS_CH0_GPIO,
        .speed_mode = LEDC_LS_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_LS_TIMER
    },
    {
        .channel    = LEDC_LS_CH1_CHANNEL,
        .duty       = 0,
        .gpio_num   = LEDC_LS_CH1_GPIO,
        .speed_mode = LEDC_LS_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_LS_TIMER
    },
};

void outputs_init(void)
{
    uint8_t ch;
    ledc_timer_config_t ledc_timer = 
    {
        .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
        .freq_hz = 5000,                      // frequency of PWM signal
        .speed_mode = LEDC_LS_MODE,           // timer mode
        .timer_num = LEDC_LS_TIMER,            // timer index
        .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock
    };

    ledc_timer_config(&ledc_timer);

    for (ch = 0; ch < LEDC_TEST_CH_NUM; ch++) 
    {
        ledc_channel_config(&ledc_channel[ch]);
    }
}

void outputs_setPWM(uint8_t channel, uint8_t colorValue)
{
    ledc_set_duty(ledc_channel[channel].speed_mode, ledc_channel[channel].channel, colorValue * 32);
    ledc_update_duty(ledc_channel[channel].speed_mode, ledc_channel[channel].channel);
}