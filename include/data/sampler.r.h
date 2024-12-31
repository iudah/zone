#ifndef SAMPLER_R_H
#define SAMPLER_R_H

#include "../core/component.r.h"
#include "../volume/volume.r.h"
#include "sampler.h"
#include <zobject.r.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncomponent, ZNSampler, znsampler, /*members*/,
                /*methods*/
                Z_DECLARE_CLASS_METHOD(znvolume *, znsampler, sample_batch,
                                       zsize batch_size))

#ifdef __cplusplus
}
#endif
#endif