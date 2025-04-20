#ifndef MSE_COST_R_H
#define MSE_COST_R_H

#include <zobject.r.h>

#include "cost.r.h"
#include "mse_cost.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncost, ZNMSECost, znmsecost, /*members*/ int axis;,
                /*methods*/
)

#ifdef __cplusplus
}
#endif
#endif