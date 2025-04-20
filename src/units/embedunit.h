#ifndef EMBEDUNIT_H
#define EMBEDUNIT_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNEmbedUnit, znembedunit)

void *zn_embed(uint64_t num_embed, uint64_t embed_dim);
void zn_embed_train_weight(void *embed, bool whether_to_train_weight);

#ifdef __cplusplus
}
#endif
#endif