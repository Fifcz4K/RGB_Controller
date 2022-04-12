#ifndef _SERVER_HTTP_H_
#define _SERVER_HTTP_H_

#include "esp_http_server.h"
#include <sys/param.h>
#include <esp_event.h>
#include <esp_log.h>

#include "json_parser.h"
#include "device_config.h"
#include "device_task_handler.h"

void startServerHttp(void);

#endif