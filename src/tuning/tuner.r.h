#ifndef TUNER_R_H
#define TUNER_R_H

#include <zobject.r.h>

#include "../core/component.r.h"
#include "tuner.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncomponent, ZNTuner, zntuner, /*members*/,
                /*methods*/
                Z_DECLARE_CLASS_METHOD(void, zntuner, update_network_weights,
                                       void *prediction))

#ifdef __cplusplus
}
#endif
#endif