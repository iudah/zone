#include "../../include/tuning/tuner.r.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

void zntuner_update_weights(void *tuner, void *weights) {
  zntuner_class *class = (zntuner_class *)zclassof((zobject *)tuner);
  assert((*class).update_weights);
  return (*class).update_weights(tuner, weights);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNTuner, zntuner,
                           Z_SELECTOR_PAIR(zntuner, update_weights))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNTuner, ZNComponent,
                             zntuner_class_constructor, NULL)
