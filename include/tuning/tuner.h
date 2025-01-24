#ifndef TUNER_H
#define TUNER_H

#include <zobject.h>
#include <zode.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNTuner, zntuner)

void zntuner_update_weights(void *tuner, void *weights);

#ifdef __cplusplus
}
#endif
#endif