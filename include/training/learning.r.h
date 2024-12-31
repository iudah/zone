#ifndef LEARNING_R_H
#define LEARNING_R_H

#include "../core/component.r.h"
#include "../data/sampler.r.h"
#include "learning.h"
#include <zobject.r.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncomponent, ZNLearning, znlearning, /*members*/,
                /*methods*/
                Z_DECLARE_CLASS_METHOD(void, znlearning, learn,
                                       znsampler *data))

#ifdef __cplusplus
}
#endif
#endif