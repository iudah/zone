#ifndef UNIT_H
#define UNIT_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNUnit, znunit)

void *znunit_compute(znunit *unit, void *input);

#ifdef __cplusplus
}
#endif
#endif