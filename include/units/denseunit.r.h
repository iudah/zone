#ifndef DENSEUNIT_R_H
#define DENSEUNIT_R_H

#include "../triggers/trigger.h"
#include "denseunit.h"
#include "unit.r.h"
#include <zobject.r.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(znunit, ZNDenseUnit, zndenseunit,
                /*members*/ uint32_t num_units;
                zntrigger * activation; void *weights; void *biases;,
                /*methods*/)

#ifdef __cplusplus
}
#endif
#endif