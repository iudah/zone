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

#include "denseunit.r.h"
#include "unit.h"

void *zn_dense(uint64_t out_dim, uint64_t in_dim, void *activator, void *weight,
               void *bias) {
  return znew(ZNDenseUnit, out_dim, in_dim, activator, weight, bias, nullptr);
}

static void zn_dense_train(void *var_node, bool whether_to_train) {
  if (!whether_to_train) {
    zode_stop_gradient(var_node);
  } else {
    zode_continue_gradient(var_node);
  }
}

void zn_dense_train_weight(void *dense, bool whether_to_train_weight) {
  return zn_dense_train(((zndenseunit *)dense)->weights,
                        whether_to_train_weight);
}
void zn_dense_train_bias(void *dense, bool whether_to_train_bias) {
  return zn_dense_train(((zndenseunit *)dense)->biases, whether_to_train_bias);
}

zndenseunit *zndenseunit_constructor(zndenseunit *denseunit, va_list *argp) {
  denseunit->num_units = va_arg(*argp, uint64_t);
  int num_in = va_arg(*argp, uint64_t);
  denseunit->activation = va_arg(*argp, zntrigger *);

  denseunit->weights = va_arg(*argp, void *);
  if (!denseunit->weights) {
    denseunit->weights =
        zode_random(2, (uint32_t[]){num_in, denseunit->num_units});
  }

  denseunit->biases = va_arg(*argp, void *);
  if (!denseunit->biases) {
    denseunit->biases = zode_random(2, (uint32_t[]){1, denseunit->num_units});
  }

  return denseunit;
}

static void *compute(zndenseunit *denseunit, void *input) {
  // printf("DenseUnit: Computing with %" PRIu32 " units.\n",
        // denseunit->num_units);

  // zode_puts(denseunit->weights, stdout);

  return zntrigger_trigger(
      denseunit->activation,
      zode_add(zode_matmul(input, denseunit->weights), denseunit->biases));
}

static void initialize(zndenseunit *denseunit) {
  printf("DenseUnit initialized with %" PRIu32 " units.\n",
         denseunit->num_units);
}

static char *describe(zndenseunit *denseunit) {
  ZN_QUICK_DESCRIBE(buffer, "DenseUnit with %" PRIu32 " units.",
                    denseunit->num_units);
  return buffer;
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNUnit, znunit, )

Z_INIT_CLASS_WITH_PRIORITIES(134, ZNDenseUnit, ZNUnit, NULL, zctor,
                             zndenseunit_constructor, znunit_compute, compute,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe, NULL)
