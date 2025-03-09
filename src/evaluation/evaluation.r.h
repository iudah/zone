#ifndef EVALUATION_R_H
#define EVALUATION_R_H

#include <zobject.r.h>

#include "../core/component.r.h"
#include "../data/sampler.h"
#include "evaluation.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncomponent, ZNEvaluation, znevaluation, /*members*/,
                /*methods*/
                Z_DECLARE_CLASS_METHOD(float, znevaluation, compute_metric,
                                       znsampler *data))

#ifdef __cplusplus
}
#endif
#endif