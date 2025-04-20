#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

#include "supervised_learning.r.h"

const zclazz *ZNSupervisedLearning;

typedef struct ZNSupervisedLearning_class znsupervisedlearning_class;
typedef struct ZNSupervisedLearning znsupervisedLearning;

void *zn_supervised_learning(void *network, void *cost, void *tuner) {
  return znew(ZNSupervisedLearning, network, cost, tuner, NULL);
}

static void train(znsupervisedlearning *learning, znsampler *data,
                  uint64_t n_iterations) {
  printf("Supervised learning training started.\n");
  Z_SUPER_CALL(learning, znlearning_train, data, n_iterations);
  printf("Training complete.\n");
}

static void initialize(znsupervisedlearning *learning) {
  zncomponent_initialize((zncomponent *)learning->_.network);
  zncomponent_initialize((zncomponent *)learning->_.cost_function);
  zncomponent_initialize((zncomponent *)learning->_.tuner);
  printf("SupervisedLearning initialized.\n");
}

static char *describe() {
  return "SupervisedLearning framework with associated components.";
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNSupervisedLearning, znsupervisedlearning, )

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNSupervisedLearning, ZNLearning, NULL,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe, znlearning_train,
                             train, NULL)
