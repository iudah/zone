#ifndef COMPONENT_R_H
#define COMPONENT_R_H

#include "component.h"
#include <zclazz.r.h>
#include <zobject.r.h>
#include <zobjectdef.r.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zobject, ZNComponent, zncomponent, /*members*/,
                Z_DECLARE_CLASS_METHOD(void, zncomponent, initialize);
                Z_DECLARE_CLASS_METHOD(char *, zncomponent, describe))

#ifdef __cplusplus
}
#endif
#endif