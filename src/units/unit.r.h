#ifndef UNIT_R_H
#define UNIT_R_H

#include <zobject.r.h>

#include "../core/processor.r.h"
#include "unit.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(
    znprocessor, ZNUnit, znunit, /*members*/,
    /*methods*/ Z_DECLARE_CLASS_METHOD(void *, znunit, compute, void *input))

#ifdef __cplusplus
}
#endif
#endif