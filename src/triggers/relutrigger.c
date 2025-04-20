#include <assert.h>
#include <string.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zobjectdef.r.h>
#include <zode.h>
#include <zot.h>

#include "relutrigger.r.h"

void *zn_relu() { return znew(ZNReluTrigger, NULL); }

static void *trigger(znrelutrigger *trigger, void *input) {
  return zode_relu(input);
}

static void initialize() { printf("ReLU activation initialized.\n"); }

static char *description = "ReLU Activation Function";
static char *describe() {
  char *buffer = zcalloc(26, 1);
  memcpy(buffer, description, 25);
  return buffer;
}

static void process() { printf("Processing ReLU activation.\n"); }

Z_DEFINE_CLASS_CONSTRUCTOR(ZNReluTrigger, znrelutrigger, )

Z_INIT_CLASS_WITH_PRIORITIES(136, ZNReluTrigger, ZNTrigger, NULL,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe,
                             znprocessor_process, process, zntrigger_trigger,
                             trigger, NULL)