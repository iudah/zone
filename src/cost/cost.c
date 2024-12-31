#include "../../include/cost/cost.r.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

void zncost_compute(zncost *cost, float *prediction, float *target) {
  zncost_class *class = (zncost_class *)zclassof((zobject *)cost);
  assert((*class).compute);
  return (*class).compute(cost, prediction, target);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNCost, zncost, Z_SELECTOR_PAIR(zncost, compute))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNCost, ZNComponent, zncost_class_constructor,
                             NULL)
