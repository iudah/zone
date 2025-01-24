#ifndef COMPONENT_R_H
#define COMPONENT_R_H

#include "component.h"
#include <zclazz.r.h>
#include <zobject.r.h>
#include <zobjectdef.r.h>
#include <zot.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(zobject, ZNComponent, zncomponent, /*members*/,
                Z_DECLARE_CLASS_METHOD(void, zncomponent, initialize);
                Z_DECLARE_CLASS_METHOD(char *, zncomponent, describe))

#define ZN_QUICK_DESCRIBE(buffer, fmt, ...)                                    \
  char *buffer = zcalloc(256, sizeof(*buffer));                                \
                                                                               \
  zsize description_length = snprintf(buffer, 256, fmt, ##__VA_ARGS__);        \
  if (description_length < 256) {                                              \
                                                                               \
    void *tmp = zrealloc(buffer, description_length);                          \
                                                                               \
    if (!tmp) {                                                                \
      LOG("unable to reallocate memory at %s %s %d\n", __FUNCTION__, __FILE__, \
          __LINE__);                                                           \
    }                                                                          \
    buffer = tmp;                                                              \
  }

#ifdef __cplusplus
}
#endif
#endif