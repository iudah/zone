#ifndef SOFTMAXTRIGGER_H
#define SOFTMAXTRIGGER_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNSoftMaxTrigger, znsoftmaxtrigger)

void *zn_softmax(int axis);

#ifdef __cplusplus
}
#endif
#endif