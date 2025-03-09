#ifndef SEQUENTIAL_NETWORK_R_H
#define SEQUENTIAL_NETWORK_R_H

#include <zobject.r.h>

#include "network.h"
#include "network.r.h"
#include "zmemory.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(znnetwork, ZNSequentialNetwork, znsequentialnetwork,
                /*members*/,
                /*methods*/)

#ifdef __cplusplus
}
#endif
#endif