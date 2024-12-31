#include "../../include/network/network.r.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

void znnetwork_add_unit(znnetwork *network, znunit *unit) {
  znnetwork_class *class = (znnetwork_class *)zclassof((zobject *)network);
  assert((*class).add_unit);
  return (*class).add_unit(network, unit);
}

void znnetwork_train(znnetwork *network) {
  znnetwork_class *class = (znnetwork_class *)zclassof((zobject *)network);
  assert((*class).train);
  return (*class).train(network);
}

void znnetwork_evaluate(znnetwork *network) {
  znnetwork_class *class = (znnetwork_class *)zclassof((zobject *)network);
  assert((*class).evaluate);
  return (*class).evaluate(network);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNNetwork, znnetwork,
                           Z_SELECTOR_PAIR(znnetwork, add_unit),
                           Z_SELECTOR_PAIR(znnetwork, train),
                           Z_SELECTOR_PAIR(znnetwork, evaluate))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNNetwork, ZNProcessor,
                             znnetwork_class_constructor, NULL)
