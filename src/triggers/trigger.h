#ifndef TRIGGER_H
#define TRIGGER_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNTrigger, zntrigger)

void *zntrigger_trigger(zntrigger *trigger, void *input);

#ifdef __cplusplus
}
#endif
#endif