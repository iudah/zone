#ifndef BATCH_SAMPLER_R_H
#define BATCH_SAMPLER_R_H

#include "batch_sampler.h"
#include "sampler.r.h"
#include <zobject.r.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(znsampler, ZNBatchSampler, znbatchsampler,
                /*members*/ void **data;
                ,
                /*methods*/
)

#ifdef __cplusplus
}
#endif
#endif