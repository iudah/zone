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

void zn_do_nothing() { fprintf(stderr, __FUNCTION__); }

Z_DEFINE_CLASS_CONSTRUCTOR(ZNComponent, zncomponent,
                            Z_SELECTOR_PAIR(zncomponent, initialize),
                            Z_SELECTOR_PAIR(zncomponent, describe))

#if 0
static zncomponent_class *
zncomponent_class_constructor(zncomponent_class *class, va_list *argp) {
  zsuper_ctor((zclazz *)ZNComponent_class, (zobject *)class, argp);
  typedef void (*voidf)(void);
  voidf selectors[] = {(voidf)zncomponent_initialize,
                       (voidf) & class->initialize, (voidf)zncomponent_describe,
                       (voidf) & class->describe};
  zsize selectors_length = sizeof(selectors) / (2 * sizeof(*selectors));
  va_list arg;va_copy (arg,*argp);
  voidf selector;
  while ((selector = __builtin_va_arg(arg, voidf))) {
    voidf method = __builtin_va_arg(arg, voidf);
    zsize i;
    for (i = 0; i < selectors_length; i++) {
      if (selectors[i * 2] == selector)
        memcpy(selectors[i * 2 + 1], &method, sizeof(method));
    }
    if (i == selectors_length) {
      fprintf(stderr,
              "[LOG]: "
              "%s (%p, %p) ignored %"
              "ll"
              "u"
              "\n"
              "\n",
              __FUNCTION__, selector, method, selectors_length);
    }
  }
  va_end(arg);
  return class;
}
#endif

Z_INIT_CLASS_WITH_PRIORITIES(120, ZNComponent, ZObject,
                             zncomponent_class_constructor, NULL)
