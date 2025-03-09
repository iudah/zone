#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>

#include "sgd_tuner.r.h"

znsgdtuner *znsgdtuner_constructor(znsgdtuner *tuner, va_list *argp) {
  tuner->learning_rate =
      zode_full_tensor(1, (uint32_t[]){1}, (float)va_arg(*argp, double));

  return tuner;
}

static void update_network_weights(znsgdtuner *tuner, void *prediction) {
  zode_sgd(prediction, tuner->learning_rate);
}

static void initialize(znsgdtuner *tuner) {
  float learning_rate;
  if (!zode_get_element(tuner->learning_rate, (int[]){1}, &learning_rate)) {
    LOG_ERROR("Failed to get learning rate.");
  }
  printf("SGD Tuner initialized with learning rate: %g\n", learning_rate);
}

static char *describe(znsgdtuner *sgdtuner) {
  float learning_rate;
  if (!zode_get_element(sgdtuner->learning_rate, (int[]){1}, &learning_rate)) {
    LOG_ERROR("Failed to get learning rate.");
  }
  ZN_QUICK_DESCRIBE(buffer, "SGD Tuner with learning rate %g", learning_rate);
  return buffer;
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNSGDTuner, znsgdtuner, )

Z_INIT_CLASS_WITH_PRIORITIES(134, ZNSGDTuner, ZNTuner, NULL, zctor,
                             znsgdtuner_constructor,
                             zntuner_update_network_weights,
                             update_network_weights, zncomponent_initialize,
                             initialize, zncomponent_describe, describe, NULL)
