#include "../../include/cost/cost.r.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>

void zncost_compute_gradients(void *self) {
  zncost *cost = self;
  zode_backward(cost->loss);
}

void *zncost_compute_loss(void *cost, void *prediction, void *target) {
  zncost_class *class = (zncost_class *)zclassof((zobject *)cost);
  assert((*class).compute_loss);
  zncost *self = cost;
  if (self->loss)
    zode_destroy(self->loss);
  return self->loss = (*class).compute_loss(cost, prediction, target);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNCost, zncost,
                           Z_SELECTOR_PAIR(zncost, compute_loss))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNCost, ZNComponent, zncost_class_constructor,
                             NULL)
