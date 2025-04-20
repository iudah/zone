#ifndef LEARNING_H
#define LEARNING_H

#include <zobject.h>

#include "../data/sampler.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNLearning, znlearning)

void znlearning_train(znlearning *learning, znsampler *data,
                      uint64_t n_iterations);

#ifdef __cplusplus
}
#endif
#endif