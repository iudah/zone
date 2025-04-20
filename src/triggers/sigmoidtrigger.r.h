#ifndef SIGMOIDTRIGGER_R_H
#define SIGMOIDTRIGGER_R_H

#include <zobject.r.h>

#include "../core/processor.r.h"
#include "../units/unit.h"
#include "sigmoidtrigger.h"
#include "trigger.h"
#include "trigger.r.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zntrigger, ZNSigmoidTrigger, znsigmoidtrigger, /*members*/,
                /*methods*/)

#ifdef __cplusplus
}
#endif
#endif