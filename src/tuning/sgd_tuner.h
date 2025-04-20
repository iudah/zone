#ifndef SGD_TUNER_H
#define SGD_TUNER_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNSGDTuner, znsgdtuner)

void *zn_sgd(float learning_rate);

#ifdef __cplusplus
}
#endif
#endif