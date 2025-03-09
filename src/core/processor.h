#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNProcessor, znprocessor)

void *znprocessor_process(void *processor, void *input);

#ifdef __cplusplus
}
#endif
#endif