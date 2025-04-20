#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <triggers/trigger.h>
#include <units/embedunit.h>
#include <units/unit.h>
#include <units/unit.r.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>
#include <zot.h>

#include "bigram.h"

Z_DECLARE_CLASS(znunit, ZNBigramUnit, znbigramunit,
                /*members*/ znunit *embbeding_table;
                uint64_t vocabsize;,
                /*methods*/)

void *zn_bigram(uint64_t vocab_size) {
  return znew(ZNBigramUnit, vocab_size, nullptr);
}

static void zn_bigram_train(void *var_node, bool whether_to_train) {
  if (!whether_to_train) {
    zode_stop_gradient(var_node);
  } else {
    zode_continue_gradient(var_node);
  }
}

// void zn_bigram_train_weight(void *bigram, bool whether_to_train_weight) {
//   return zn_bigram_train(((znbigramunit *)bigram)->weights,
//                          whether_to_train_weight);
// }
// void zn_bigram_train_bias(void *bigram, bool whether_to_train_bias) {
//   return zn_bigram_train(((znbigramunit *)bigram)->biases,
//                          whether_to_train_bias);
// }

znbigramunit *znbigramunit_constructor(znbigramunit *bigramunit,
                                       va_list *argp) {
  bigramunit->vocabsize = va_arg(*argp, uint64_t);

  bigramunit->embbeding_table =
      zn_embed(bigramunit->vocabsize, bigramunit->vocabsize);

  return bigramunit;
}

static void *compute(znbigramunit *bigramunit, void *input) {
  // printf("BigramUnit: Computing with %" PRIu32 " units.\n",
  // bigramunit->num_units);

  // zode_puts(bigramunit->weights, stdout);

  void *logits = znunit_compute(bigramunit->embbeding_table, input);

  return logits;
}

void initialize(znbigramunit *bigramunit) {
  printf("BigramUnit initialized with %" PRIu64 " vocab size.\n",
         bigramunit->vocabsize);
}

char *describe(znbigramunit *bigramunit) {
  ZN_QUICK_DESCRIBE(buffer, "BigramUnit with %" PRIu64 " vocab size.",
                    bigramunit->vocabsize);
  return buffer;
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNUnit, znunit, )

Z_INIT_CLASS_WITH_PRIORITIES(134, ZNBigramUnit, ZNUnit, NULL, zctor,
                             znbigramunit_constructor, znunit_compute, compute,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe, NULL)
