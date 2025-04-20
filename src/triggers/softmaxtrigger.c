#include <assert.h>
#include <math.h>
#include <string.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zobjectdef.r.h>
#include <zode.h>
#include <zot.h>

#include "softmaxtrigger.r.h"

void *zn_softmax(int axis) { return znew(ZNSoftMaxTrigger, axis, NULL); }

znsoftmaxtrigger *znsoftmaxtrigger_constructor(znsoftmaxtrigger *trigger,
                                               va_list *argp) {
  Z_SUPER_CALL(trigger, zctor, argp);
  trigger->axis = va_arg(*argp, int);

  return trigger;
}

static void *trigger(znsoftmaxtrigger *trigger, void *input) {
  return zode_softmax(input, trigger->axis);
}

static void initialize() { printf("SoftMax activation initialized.\n"); }

static char *description = "SoftMax Activation Function";
static char *describe() {
  char *buffer = zcalloc(26, 1);
  memcpy(buffer, description, 26);
  return buffer;
}

static void process() { printf("Processing SoftMax activation.\n"); }

Z_DEFINE_CLASS_CONSTRUCTOR(ZNSoftMaxTrigger, znsoftmaxtrigger, )

Z_INIT_CLASS_WITH_PRIORITIES(136, ZNSoftMaxTrigger, ZNTrigger, NULL, zctor,
                             znsoftmaxtrigger_constructor,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe,
                             znprocessor_process, process, zntrigger_trigger,
                             trigger, NULL)