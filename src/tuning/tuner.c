#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

#include "tuner.r.h"

void zntuner_update_network_weights(void *tuner, void *prediction) {
  zntuner_class *class = (zntuner_class *)zclassof((zobject *)tuner);
  assert((*class).update_network_weights);
  return (*class).update_network_weights(tuner, prediction);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNTuner, zntuner,
                           Z_SELECTOR_PAIR(zntuner, update_network_weights))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNTuner, ZNComponent,
                             zntuner_class_constructor, NULL)
