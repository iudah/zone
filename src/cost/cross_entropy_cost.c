#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>

#include "cross_entropy_cost.r.h"

void *zn_cross_entropy(int axis) {
  return znew(ZNCrossEntropyCost, axis, NULL);
}

static zncrossentropycost *constructor(zncrossentropycost *cost,
                                       va_list *argp) {
  Z_SUPER_CALL(cost, zctor, argp);
  cost->axis = va_arg(*argp, int);

  return cost;
}

static zode *compute_loss(zncrossentropycost *cost, void *predictions,
                          void *targets) {
  return zode_cross_entropy(targets, predictions, cost->axis);
}

static void initialize(zncrossentropycost *cost) {
  printf("CrossEntropy Cost Function initialized.\n");
}

static char *description = "Cross Entropy Cost Function";
static char *describe(zncrossentropycost *cost) {
  char *buffer = zcalloc(34, 1);
  memcpy(buffer, description, 33);
  return buffer;
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNCrossEntropyCost, zncrossentropycost, )

Z_INIT_CLASS_WITH_PRIORITIES(134, ZNCrossEntropyCost, ZNCost, NULL, zctor,
                             constructor, zncost_compute_loss, compute_loss,
                             NULL)
