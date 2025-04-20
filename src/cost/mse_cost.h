#ifndef MSE_COST_H
#define MSE_COST_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNMSECost, znmsecost)

void *zn_mse(int axis);

#ifdef __cplusplus
}
#endif
#endif