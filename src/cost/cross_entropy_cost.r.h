#ifndef CROSSENTROPY_COST_R_H
#define CROSSENTROPY_COST_R_H

#include <zobject.r.h>

#include "cost.r.h"
#include "cross_entropy_cost.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncost, ZNCrossEntropyCost, zncrossentropycost,
                /*members*/ int axis;
                ,
                /*methods*/
)

#ifdef __cplusplus
}
#endif
#endif