#ifndef SAMPLER_H
#define SAMPLER_H

#include <zobject.h>

#include "../volume/volume.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNSampler, znsampler)

void **znsampler_sample_batch(void *sampler, zsize batch_size, zsize *n_batch);

#ifdef __cplusplus
}
#endif
#endif