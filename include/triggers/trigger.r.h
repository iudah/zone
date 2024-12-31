#ifndef TRIGGER_R_H
#define TRIGGER_R_H

#include "../core/processor.r.h"
#include "../units/unit.h"
#include "trigger.h"
#include <zobject.r.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(
    znprocessor, ZNTrigger, zntrigger, /*members*/,
    /*methods*/ Z_DECLARE_CLASS_METHOD(void, zntrigger, trigger, float input))

#ifdef __cplusplus
}
#endif
#endif