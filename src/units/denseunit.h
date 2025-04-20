#ifndef DENSEUNIT_H
#define DENSEUNIT_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNDenseUnit, zndenseunit)

void *zn_dense(uint64_t out_dim, uint64_t in_dim, void *activator, void *weight,
               void *bias);
void zn_dense_train_weight(void *dense, bool whether_to_train_weight);
void zn_dense_train_bias(void *dense, bool whether_to_train_bias);

#ifdef __cplusplus
}
#endif
#endif