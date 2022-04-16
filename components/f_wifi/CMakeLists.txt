idf_component_register(SRCS "f_wifi.c"
                    INCLUDE_DIRS "."
                    REQUIRES common f_eeprom esp_wifi nvs_flash)
