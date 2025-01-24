#ifndef PROCESSOR_R_H
#define PROCESSOR_R_H

#include "component.r.h"
#include "processor.h"
#include <zobject.r.h>
#include <zobjectdef.r.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zncomponent, ZNProcessor, znprocessor, /*members*/,
                /*methods*/
                Z_DECLARE_CLASS_METHOD(void *, znprocessor, process,
                                       void *input))

#ifdef __cplusplus
}
#endif
#endif