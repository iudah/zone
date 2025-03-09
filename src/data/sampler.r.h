#ifndef SAMPLER_R_H
#define SAMPLER_R_H

#include <zobject.r.h>

#include "../core/component.r.h"
#include "../volume/volume.r.h"
#include "sampler.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncomponent, ZNSampler, znsampler, /*members*/,
                /*methods*/
                Z_DECLARE_CLASS_METHOD(void **, znsampler, sample_batch,
                                       zsize batch_size, zsize *n_batch))

#ifdef __cplusplus
}
#endif
#endif