#include "processor.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zobjectdef.r.h>

#include "processor.r.h"

void *znprocessor_process(void *processor, void *input) {
  znprocessor_class *class =
      (znprocessor_class *)zclassof((zobject *)processor);
  assert((*class).process);
  return (*class).process(processor, input);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNProcessor, znprocessor,
                           Z_SELECTOR_PAIR(znprocessor, process))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNProcessor, ZNComponent,
                             znprocessor_class_constructor, NULL)
