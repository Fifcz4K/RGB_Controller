idf_component_register(SRCS "json_parser.c"
                    INCLUDE_DIRS "."
                    REQUIRES common cJSON device_config f_wifi)
