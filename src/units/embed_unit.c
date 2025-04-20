#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>
#include <zot.h>

#include "embedunit.r.h"
#include "unit.h"

void *zn_embed(uint64_t n_embed, uint64_t embed_dim) {
  return znew(ZNEmbedUnit, n_embed, embed_dim, nullptr);
}

static void zn_embed_train(void *var_node, bool whether_to_train) {
  if (!whether_to_train) {
    zode_stop_gradient(var_node);
  } else {
    zode_continue_gradient(var_node);
  }
}

void zn_embed_train_weight(void *embed, bool whether_to_train_weight) {
  return zn_embed_train(((znembedunit *)embed)->embed_table,
                        whether_to_train_weight);
}

znembedunit *znembedunit_constructor(znembedunit *embedunit, va_list *argp) {
  embedunit->num_embed = va_arg(*argp, uint64_t);
  embedunit->embed_dim = va_arg(*argp, uint64_t);

  embedunit->embed_table =
      zode_random(2, (uint32_t[]){embedunit->num_embed, embedunit->embed_dim});
  if (!embedunit->embed_table) {
  }

  return embedunit;
}

static void *compute(znembedunit *embedunit, void *input) {
  return zode_embed(embedunit->embed_table, input);
}

static void initialize(znembedunit *embedunit) {
  printf("EmbedUnit initialized with %" PRIu32 " units.\n",
         embedunit->num_embed);
}

static char *describe(znembedunit *embedunit) {
  ZN_QUICK_DESCRIBE(buffer, "EmbedUnit with %" PRIu32 " units.",
                    embedunit->num_embed);
  return buffer;
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNUnit, znunit, )

Z_INIT_CLASS_WITH_PRIORITIES(134, ZNEmbedUnit, ZNUnit, NULL, zctor,
                             znembedunit_constructor, znunit_compute, compute,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe, NULL)
