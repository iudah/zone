#include <assert.h>
#include <math.h>
#include <string.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zobjectdef.r.h>
#include <zode.h>
#include <zot.h>

#include "sigmoidtrigger.r.h"

void *zn_sigmoid() { return znew(ZNSigmoidTrigger, NULL); }

static void *trigger(znsigmoidtrigger *trigger, void *input) {
  return zode_sigmoid(input);
}

static void initialize() { printf("Sigmoid activation initialized.\n"); }

static char *description = "Sigmoid Activation Function";
static char *describe() {
  char *buffer = zcalloc(26, 1);
  memcpy(buffer, description, 26);
  return buffer;
}

static void process() { printf("Processing Sigmoid activation.\n"); }

Z_DEFINE_CLASS_CONSTRUCTOR(ZNSigmoidTrigger, znsigmoidtrigger, )

Z_INIT_CLASS_WITH_PRIORITIES(136, ZNSigmoidTrigger, ZNTrigger, NULL,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe,
                             znprocessor_process, process, zntrigger_trigger,
                             trigger, NULL)