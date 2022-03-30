#ifndef _SERVER_HTTP_H_
#define _SERVER_HTTP_H_

#include "esp_http_server.h"

#include "common.h"
#include "json_parser.h"
#include "device_config.h"

void startServerHttp(void);

#endif