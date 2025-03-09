#include <assert.h>
#include <string.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>

#include "../core/processor.h"
#include "learning.r.h"

const zclazz *ZNLearning;

typedef struct ZNLearning_class znlearning_class;
typedef struct ZNLearning znlearning;

znlearning *znlearning_constructor(znlearning *learning, va_list *argp) {
  learning->network = va_arg(*argp, znnetwork *);
  learning->cost_function = va_arg(*argp, zncost *);
  learning->tuner = va_arg(*argp, zntuner *);

  return learning;
}

void train(znlearning *learning, znsampler *data) {
  zsize num_batch = 0;
  void **batch = znsampler_sample_batch(data, 32, &num_batch); // Sample batches
  for (zsize i = 0; i < num_batch; i++) {
    void *input = batch[i * 2];
    void *output = batch[i * 2 + 1];

    // Forward pass
    void *prediction = znprocessor_process(learning->network, input);

    // Objective loss
    zncost_compute_loss(learning->cost_function, prediction, output);

    // Loss gradients
    zncost_compute_gradients(learning->cost_function);

    // Update weights
    zntuner_update_network_weights(learning->tuner, prediction);

    // Clean up tensors
    prediction = NULL;
    // zode_destroy(prediction);
    // zode_destroy_tensor(input);
    // todo: manage destroys of objects
  }
}

void znlearning_train(znlearning *learning, znsampler *data) {
  znlearning_class *class = (znlearning_class *)zclassof((zobject *)learning);
  assert((*class).train);
  return (*class).train(learning, data);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNLearning, znlearning,
                           Z_SELECTOR_PAIR(znlearning, train))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNLearning, ZNComponent,
                             znlearning_class_constructor, zctor,
                             znlearning_constructor, znlearning_train, train,
                             NULL)
