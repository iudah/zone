#include "../../include/core/component.h"
#include "../../include/core/component.r.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zobjectdef.r.h>

void zncomponent_initialize(zncomponent *component) {
  zncomponent_class *class =
      (zncomponent_class *)zclassof((zobject *)component);
  assert(class && (*class).initialize);
  return (*class).initialize(component);
}
char *zncomponent_describe(zncomponent *component) {
  zncomponent_class *class =
      (zncomponent_class *)zclassof((zobject *)component);
  assert((*class).describe);
  return (*class).describe(component);
}

void zn_do_nothing() { fprintf(stderr, __PRETTY_FUNCTION__); }

Z_DEFINE_CLASS_CONSTRUCTOR(ZNComponent, zncomponent,
                           Z_SELECTOR_PAIR(zncomponent, initialize),
                           Z_SELECTOR_PAIR(zncomponent, describe))

Z_INIT_CLASS_WITH_PRIORITIES(120, ZNComponent, ZObject,
                             zncomponent_class_constructor, NULL)

