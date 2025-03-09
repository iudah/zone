#include "../src/cost/mse_cost.h"
#include "../src/data/batch_sampler.h"
#include "../src/evaluation/accuracy_evaluation.h"
#include "../src/evaluation/evaluation.h"
#include "../src/network/network.h"
#include "../src/network/sequential_network.h"
#include "../src/training/learning.h"
#include "../src/training/supervised_learning.h"
#include "../src/triggers/relutrigger.h"
#include "../src/tuning/sgd_tuner.h"
#include "../src/units/denseunit.h"
#include <stdio.h>
#include <string.h>
#include <zode.h>

int main() {

  // Create components
  auto relu = znew(ZNReluTrigger, NULL);
  auto dense_layer = znew(ZNDenseUnit, 2, 2, relu, NULL);
  auto network = znew(ZNSequentialNetwork, NULL);
  znnetwork_add_unit((void *)network, (void *)dense_layer);
  auto cost = znew(ZNMSECost, NULL);
  auto tuner = znew(ZNSGDTuner, 0.01, NULL);

  // Set up learning
  auto learning = znew(ZNSupervisedLearning, network, cost, tuner, NULL);

  // Train and evaluate
  auto *data_sampler = znew(
      ZNBatchSampler,
      /*x    */ zode_from_array(2, (uint32_t[]){1, 2}, (float[]){0.1f, 0.9f}),
      /*y_hat*/ zode_from_array(2, (uint32_t[]){1, 2}, (float[]){0.01f, 0.99f}),
      NULL);
  znlearning_train((void *)learning, (void *)data_sampler);

  void *prediction = znnetwork_evaluate(
      network, zode_from_array(2, (uint32_t[]){1, 2}, (float[]){0.1f, 0.9f}));

  zode_puts(prediction, stdout);

  // auto *evaluation = znew(ZNAccuracyEvaluation, NULL);
  // float accuracy =
  //     znevaluation_compute_metric((void *)evaluation, (void
  //     *)data_sampler);

  // printf("Accuracy: %g\n", accuracy);

  zdelete(tuner);
  zdelete(cost);
  zdelete(network);
  zdelete(dense_layer);
  zdelete(relu);

  return 0;
}
