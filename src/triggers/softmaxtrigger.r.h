#ifndef SOFTMAXTRIGGER_R_H
#define SOFTMAXTRIGGER_R_H

#include <zobject.r.h>

#include "../core/processor.r.h"
#include "../units/unit.h"
#include "softmaxtrigger.h"
#include "trigger.h"
#include "trigger.r.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zntrigger, ZNSoftMaxTrigger, znsoftmaxtrigger,
                /*members*/ int axis;
                ,
                /*methods*/)

#ifdef __cplusplus
}
#endif
#endif