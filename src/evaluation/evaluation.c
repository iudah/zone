#include "../../include/evaluation/evaluation.r.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

const zclazz *ZNEvaluation;

typedef struct ZNEvaluation_class znevaluation_class;
typedef struct ZNEvaluation znevaluation;

void znevaluation_compute_metric(znevaluation *evaluation, znsampler *data) {
  znevaluation_class *class =
      (znevaluation_class *)zclassof((zobject *)evaluation);
  assert((*class).compute_metric);
  return (*class).compute_metric(evaluation, data);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNEvaluation, znevaluation,
                           Z_SELECTOR_PAIR(znevaluation, compute_metric))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNEvaluation, ZNComponent,
                             znevaluation_class_constructor, NULL)
