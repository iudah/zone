#ifndef NETWORK_R_H
#define NETWORK_R_H

#include "../core/processor.r.h"
#include "../units/unit.h"
#include "network.h"
#include <zobject.r.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(znprocessor, ZNNetwork, znnetwork, /*members*/ znunit *units;
                ,
                /*methods*/
                Z_DECLARE_CLASS_METHOD(void, znnetwork, add_unit, znunit *unit);
                Z_DECLARE_CLASS_METHOD(void, znnetwork, train);
                Z_DECLARE_CLASS_METHOD(void, znnetwork, evaluate))

#ifdef __cplusplus
}
#endif
#endif