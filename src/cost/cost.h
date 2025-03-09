#ifndef COST_H
#define COST_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNCost, zncost)

void *zncost_compute_loss(void *cost, void *prediction, void *target);
void zncost_compute_gradients(void *cost);

#ifdef __cplusplus
}
#endif
#endif
