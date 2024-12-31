#include "../../include/training/learning.r.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

const zclazz *ZNLearning;

typedef struct ZNLearning_class znlearning_class;
typedef struct ZNLearning znlearning;

void znlearning_learn(znlearning *learning, znsampler *data) {
  znlearning_class *class = (znlearning_class *)zclassof((zobject *)learning);
  assert((*class).learn);
  return (*class).learn(learning, data);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNLearning, znlearning,
                           Z_SELECTOR_PAIR(znlearning, learn))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNLearning, ZNComponent,
                             znlearning_class_constructor, NULL)
