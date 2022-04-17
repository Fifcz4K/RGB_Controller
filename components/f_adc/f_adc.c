#include "f_adc.h"

static esp_adc_cal_characteristics_t *adc_chars;

static void print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        printf("Characterized using Two Point Value\n");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        printf("Characterized using eFuse Vref\n");
    } else {
        printf("Characterized using Default Vref\n");
    }
}

static void check_efuse(void)
{
    //Check if TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }
    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
}

void adcInit(void)
{
    check_efuse();

    adc1_config_width(ADC_WIDTH);
    // adc1_config_channel_atten(adcLightChannel, ADC_ATTEN);
    adc1_config_channel_atten(adcTemperatureChannel, ADC_ATTEN);

    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT, ADC_ATTEN, ADC_WIDTH, ADC_DEFAULT_VREF, adc_chars);
    print_char_val_type(val_type);
}

adc_value_t adcGetValue(channel_adc_t channel)
{
    adc_value_t adcValue = 0;
    for(uint8_t i = 0; i < ADC_NO_OF_SAMPLES; i++)
    {
        adcValue += adc1_get_raw((adc1_channel_t)channel);
    }

    adcValue /= ADC_NO_OF_SAMPLES;

    return adcValue;
}
