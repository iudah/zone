#ifndef COMPONENT_H
#define COMPONENT_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNComponent, zncomponent)

char *zncomponent_describe(zncomponent *component);
void zncomponent_initialize(zncomponent *component);

#ifdef __cplusplus
}
#endif
#endif