#include "../../include/triggers/relutrigger.r.h"

#include <assert.h>
#include <math.h>
#include <string.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zobjectdef.r.h>
#include <zot.h>

static float trigger(float input) { return 0; /*fmax(0.0f, input); */ }

static void initialize() { printf("ReLU activation initialized.\n"); }

static char *description = "ReLU Activation Function";
static char *describe() {
  char *buffer = zcalloc(26, 1);
  memcpy(buffer, description, 26);
  return buffer;
}

static void process() { printf("Processing ReLU activation.\n"); }

Z_DEFINE_CLASS_CONSTRUCTOR(ZNReluTrigger, znrelutrigger, )

Z_INIT_CLASS_WITH_PRIORITIES(136, ZNReluTrigger, ZNTrigger, NULL,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe,
                             znprocessor_process, process, zntrigger_trigger,
                             trigger, NULL)