#ifndef BATCH_SAMPLER_R_H
#define BATCH_SAMPLER_R_H

#include <zobject.r.h>

#include "batch_sampler.h"
#include "sampler.r.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(znsampler, ZNBatchSampler, znbatchsampler,
                /*members*/ void *inputs;
                void *labels;,
                /*methods*/
)

#ifdef __cplusplus
}
#endif
#endif