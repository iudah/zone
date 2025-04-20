#ifndef SUPERVISED_LEARNING_H
#define SUPERVISED_LEARNING_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNSupervisedLearning, znsupervisedlearning)

void *zn_supervised_learning(void *network, void *cost, void *tuner);

#ifdef __cplusplus
}
#endif
#endif