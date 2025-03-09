#ifndef SGD_TUNER_R_H
#define SGD_TUNER_R_H

#include "sgd_tuner.h"
#include "tuner.r.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SGD_TUNER_H) && defined(TUNER_R_H)

Z_DECLARE_CLASS(zntuner, ZNSGDTuner, znsgdtuner,
                /*members*/ void *learning_rate;
                ,
                /*methods*/
)

#endif

#ifdef __cplusplus
}
#endif
#endif