#ifndef VOLUME_R_H
#define VOLUME_R_H

#include <zobject.r.h>

#include "../core/component.r.h"
#include "volume.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncomponent, ZNVolume, znvolume, /*member*/ void *tensor;
                ,
                /*methods*/ Z_DECLARE_CLASS_METHOD(float *, znvolume, at,
                                                   zsize *idx);
                /*methods*/ Z_DECLARE_CLASS_METHOD(void, znvolume, reshape,
                                                   uint8_t rank,
                                                   uint32_t *shape))

#ifdef __cplusplus
}
#endif
#endif