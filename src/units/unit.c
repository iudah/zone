#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

#include "unit.r.h"

void *znunit_compute(znunit *unit, void *input) {
  znunit_class *class = (znunit_class *)zclassof((zobject *)unit);
  assert((*class).compute);
  return (*class).compute(unit, input);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNUnit, znunit, Z_SELECTOR_PAIR(znunit, compute))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNUnit, ZNProcessor, znunit_class_constructor,
                             NULL)
