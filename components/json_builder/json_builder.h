#ifndef _JSON_BUILDER_H_
#define _JSON_BUILDER_H_

#include "cJSON.h"
#include "models.h"
#include "common.h"
#include "device_config.h"
#include "measurements.h"

cJSON* jsonBuildConfiguration(void);
cJSON* jsonBuildMeasurements(void);

#endif