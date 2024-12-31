#ifndef COST_R_H
#define COST_R_H

#include "../core/component.r.h"
#include "cost.h"
#include <zobject.r.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncomponent, ZNCost, zncost, /*members*/,
                /*methods*/
                Z_DECLARE_CLASS_METHOD(void, zncost, compute, float *prediction,
                                       float *targets))

#ifdef __cplusplus
}
#endif
#endif