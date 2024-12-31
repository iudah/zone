#ifndef TUNER_R_H
#define TUNER_R_H

#include "../core/component.r.h"
#include "tuner.h"
#include <zobject.r.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncomponent, ZNTuner, zntuner, /*members*/,
                /*methods*/
                Z_DECLARE_CLASS_METHOD(void, zntuner, update_weights,
                                       float *weights, float *gradients))

#ifdef __cplusplus
}
#endif
#endif