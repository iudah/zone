#ifndef EVALUATION_H
#define EVALUATION_H

#include "../data/sampler.h"
#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNEvaluation, znevaluation);

float znevaluation_compute_metric(void *evaluation, void *data);

#ifdef __cplusplus
}
#endif
#endif