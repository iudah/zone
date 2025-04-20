#ifndef BATCH_SAMPLER_H
#define BATCH_SAMPLER_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNBatchSampler, znbatchsampler)

void *zn_batch_sampler(void *input, void *label);

#ifdef __cplusplus
}
#endif
#endif