idf_component_register(SRCS "json_builder.c"
                    INCLUDE_DIRS "."
                    REQUIRES common cJSON device_config measurements)
