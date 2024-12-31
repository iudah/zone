#include "../../include/triggers/trigger.r.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zobjectdef.r.h>

void zntrigger_trigger(zntrigger *trigger, float input) {
  zntrigger_class *class = (zntrigger_class *)zclassof((zobject *)trigger);
  assert((*class).trigger);
  return (*class).trigger(trigger, input);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNTrigger, zntrigger,
                           Z_SELECTOR_PAIR(zntrigger, trigger))

Z_INIT_CLASS_WITH_PRIORITIES(134, ZNTrigger, ZNProcessor,
                             zntrigger_class_constructor, NULL)