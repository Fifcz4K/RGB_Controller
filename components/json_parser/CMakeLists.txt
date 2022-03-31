idf_component_register(SRCS "json_parser.c" "cJSON.c" "cJSON_Utils.c"
                    INCLUDE_DIRS "."
                    REQUIRES common device_config)
