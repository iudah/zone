#include "../../include/units/denseunit.r.h"
#include "../../include/units/unit.h"

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

zndenseunit *zndenseunit_constructor(zndenseunit *denseunit, va_list *argp) {

  denseunit->num_units = va_arg(*argp, int);
  denseunit->activation = va_arg(*argp, zntrigger *);

  denseunit->weights = NULL;
  denseunit->biases = zode_random(2, (uint32_t[]){1, denseunit->num_units});

  return denseunit;
}

static void compute(zndenseunit *denseunit) {
  // Simple computation (placeholder)
  printf("DenseUnit: Computing with %" PRIu32 " units.\n",
         denseunit->num_units);
}

void initialize(zndenseunit *denseunit) {
  printf("DenseUnit initialized with %" PRIu32 " units.\n",
         denseunit->num_units);
}

char *describe(zndenseunit *denseunit) {
  ZN_QUICK_DESCRIBE(buffer, "DenseUnit with %" PRIu32 " units.",
                    denseunit->num_units);
  return buffer;
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNUnit, znunit, )

Z_INIT_CLASS_WITH_PRIORITIES(134, ZNDenseUnit, ZNUnit, NULL, zctor,
                             zndenseunit_constructor, znunit_compute, compute,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe, NULL)
