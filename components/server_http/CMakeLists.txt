idf_component_register(SRCS "server_http.c"
                    INCLUDE_DIRS "."
                    REQUIRES common esp_http_server json_parser)
