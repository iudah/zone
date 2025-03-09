#include "sequential_network.h"

#include <assert.h>
#include <inttypes.h>
#include <zobject.h>
#include <zobject.r.h>

#include "sequential_network.r.h"

static void add_unit(znsequentialnetwork *sequentialnetwork, znunit *layer) {
  Z_SUPER_CALL(sequentialnetwork, znnetwork_add_unit, layer);
  printf("Layer added to SequentialNetwork.\n");
}

static void *process(znsequentialnetwork *sequentialnetwork, void *input) {
  for (zsize i = 0; i < sequentialnetwork->_.idx; i++) {
    input = znunit_compute(sequentialnetwork->_.units[i], input);
  }
  return input;
}

static void train(znsequentialnetwork *sequentialnetwork) {
  printf("Training SequentialNetwork...\n");
}

static void *evaluate(znsequentialnetwork *sequentialnetwork, void *input) {
  return process(sequentialnetwork, input);
}

static void initialize(znsequentialnetwork *sequentialnetwork) {
  for (zsize i = 0; i < sequentialnetwork->_.idx; i++) {
    zncomponent_initialize((zncomponent *)sequentialnetwork->_.units[i]);
  }
}

static char *describe(znsequentialnetwork *sequentialnetwork) {
  ZN_QUICK_DESCRIBE(buffer, "SequentialNetwork with %" PRIu64 " layers.",
                    sequentialnetwork->_.idx);
  return buffer;
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNSequentialNetwork, znsequentialnetwork, )

Z_INIT_CLASS_WITH_PRIORITIES(134, ZNSequentialNetwork, ZNNetwork, NULL,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe,
                             znprocessor_process, process, znnetwork_add_unit,
                             add_unit, znnetwork_train, train,
                             znnetwork_evaluate, evaluate, NULL)
