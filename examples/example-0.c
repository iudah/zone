#include "../include/cost/mse_cost.h"
#include "../include/data/batch_sampler.h"
#include "../include/evaluation/accuracy_evaluation.h"
#include "../include/evaluation/evaluation.h"
#include "../include/network/network.h"
#include "../include/network/sequential_network.h"
#include "../include/training/learning.h"
#include "../include/training/supervised_learning.h"
#include "../include/triggers/relutrigger.h"
#include "../include/tuning/sgd_tuner.h"
#include "../include/units/denseunit.h"
#include <string.h>

int main() {
  // Create components
  auto relu = znew(ZNReluTrigger, NULL);
  auto dense_layer = znew(ZNDenseUnit, 128, relu, NULL);
  auto network = znew(ZNSequentialNetwork, NULL);
  znnetwork_add_unit((void *)network, (void *)dense_layer);
  auto cost = znew(ZNMSECost, NULL);
  auto tuner = znew(ZNSGDTuner, 0.01, NULL);

  // Set up learning
  auto learning = znew(ZNSupervisedLearning, network, cost, tuner, NULL);

  // Train and evaluate
  auto *data_sampler = znew(ZNBatchSampler, NULL);
  znlearning_train((void *)learning, (void *)data_sampler);

  auto *evaluation = znew(ZNAccuracyEvaluation, NULL);
  float accuracy =
      znevaluation_compute_metric((void *)evaluation, (void *)data_sampler);

  printf("Accuracy: %g\n", accuracy);

#if 0

  Evaluation *evaluation = new AccuracyEvaluation();
  float accuracy = evaluation->computeMetric(dataSampler);

  std::cout << "Accuracy: " << accuracy << "%" << std::endl;

  // Clean up
  delete learning;
  delete evaluation;
  delete network;
  delete dataSampler;
#endif

  zdelete(tuner);
  zdelete(cost);
  zdelete(network);
  zdelete(dense_layer);
  zdelete(relu);

  return 0;
}
