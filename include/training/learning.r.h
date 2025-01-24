#ifndef LEARNING_R_H
#define LEARNING_R_H

#include "../core/component.r.h"
#include "../cost/cost.h"
#include "../data/sampler.h"
#include "../network/network.h"
#include "../tuning/tuner.h"
#include "learning.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncomponent, ZNLearning, znlearning, /*members*/
                znnetwork *network;
                zncost * cost_function; zntuner * tuner;
                ,
                /*methods*/
                Z_DECLARE_CLASS_METHOD(void, znlearning, train,
                                       znsampler *data))

#ifdef __cplusplus
}
#endif
#endif