#ifndef EMBEDUNIT_R_H
#define EMBEDUNIT_R_H

#include <zobject.r.h>

#include "embedunit.h"
#include "unit.r.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(znunit, ZNEmbedUnit, znembedunit,
                /*members*/
                void *embed_table;
                uint32_t num_embed; uint32_t embed_dim;,
                /*methods*/)

#ifdef __cplusplus
}
#endif
#endif