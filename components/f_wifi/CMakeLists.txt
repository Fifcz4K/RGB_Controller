idf_component_register(SRCS "wifi_handler.c" "wifi_credentials.c"
                    INCLUDE_DIRS "."
                    REQUIRES common esp_wifi nvs_flash)
