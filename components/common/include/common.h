#ifndef _COMMON_H
#define _COMMON_H

#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"

#define DELAY(delay) vTaskDelay(delay / portTICK_RATE_MS)

#endif