#ifndef RELUTRIGGER_R_H
#define RELUTRIGGER_R_H

#include "../core/processor.r.h"
#include "../units/unit.h"
#include "relutrigger.h"
#include "trigger.h"
#include "trigger.r.h"
#include <zobject.r.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zntrigger, ZNReluTrigger, znrelutrigger, /*members*/,
                /*methods*/)

#ifdef __cplusplus
}
#endif
#endif