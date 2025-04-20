#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>

#include "mse_cost.r.h"

void *zn_mse(int axis) { return znew(ZNMSECost,axis, NULL); }

static znmsecost *constructor(znmsecost *cost, va_list *argp) {
  Z_SUPER_CALL(cost, zctor, argp);
  cost->axis = va_arg(*argp, int);

  return cost;
}

static zode *compute_loss(znmsecost *cost, void *predictions, void *targets) {
  return zode_mse(targets, predictions, cost->axis);
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

Z_INIT_CLASS_WITH_PRIORITIES(134, ZNMSECost, ZNCost, NULL, zctor, constructor,
                             zncost_compute_loss, compute_loss, NULL)
