#include "../../include/units/unit.r.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

void znunit_compute(znunit *unit) {
  znunit_class *class = (znunit_class *)zclassof((zobject *)unit);
  assert((*class).compute);
  return (*class).compute(unit);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNUnit, znunit, Z_SELECTOR_PAIR(znunit, compute))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNUnit, ZNProcessor, znunit_class_constructor,
                             NULL)
