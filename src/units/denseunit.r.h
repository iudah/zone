#ifndef DENSEUNIT_R_H
#define DENSEUNIT_R_H

#include <zobject.r.h>

#include "../triggers/trigger.h"
#include "denseunit.h"
#include "unit.r.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(znunit, ZNDenseUnit, zndenseunit,
                /*members*/
                zntrigger *activation;
                void *weights; void *biases; uint32_t num_units;,
                /*methods*/)

#ifdef __cplusplus
}
#endif
#endif