#ifndef CROSSENTROPY_COST_H
#define CROSSENTROPY_COST_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNCrossEntropyCost, zncrossentropycost)

void *zn_cross_entropy(int axis);

#ifdef __cplusplus
}
#endif
#endif