#include "../../include/cost/mse_cost.r.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>

static zode *compute_loss(znmsecost *cost, void *predictions, void *targets) {
  return zode_mse(predictions, targets);
}

static void initialize(znmsecost *cost) {
  printf("MSE Cost Function initialized.\n");
}

static char *description = "Mean Squared Error Cost Function";
static char *describe(znmsecost *cost) {
  char *buffer = zcalloc(34, 1);
  memcpy(buffer, description, 33);
  return buffer;
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNMSECost, znmsecost, )

Z_INIT_CLASS_WITH_PRIORITIES(134, ZNMSECost, ZNCost, NULL, zncost_compute_loss,
                             compute_loss, NULL)
