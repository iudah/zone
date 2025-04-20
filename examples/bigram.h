#ifndef BIGRAMUNIT_H
#define BIGRAMUNIT_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNBigramUnit, znbigramunit)


void *zn_bigram(uint64_t vocab_size) ;

#ifdef __cplusplus
}
#endif
#endif