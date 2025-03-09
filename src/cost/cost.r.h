#ifndef COST_R_H
#define COST_R_H

#include <zobject.r.h>

#include "../core/component.r.h"
#include "cost.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncomponent, ZNCost, zncost, /*members*/ void *loss;
                ,
                /*methods*/
                Z_DECLARE_CLASS_METHOD(void *, zncost, compute_loss,
                                       void *prediction, void *targets))

#ifdef __cplusplus
}
#endif
#endif