#include <zode.h>

#include "../src/cost/mse_cost.h"
#include "../src/data/batch_sampler.h"
#include "../src/network/network.h"
#include "../src/network/sequential_network.h"
#include "../src/training/learning.h"
#include "../src/training/supervised_learning.h"
#include "../src/triggers/sigmoidtrigger.h"
#include "../src/tuning/sgd_tuner.h"
#include "../src/units/denseunit.h"

int main() {
  // Create components
  auto sigmoid = zn_sigmoid();
  auto dense_layer = zn_dense(
      2, 2, sigmoid,
      zode_from_array(2, (uint32_t[]){2, 2}, (float[]){.15, .25, .20, .30}),
      zode_from_array(2, (uint32_t[]){1, 1}, (float[]){.35}));
  auto hidden_layer = zn_dense(
      2, 2, sigmoid,
      zode_from_array(2, (uint32_t[]){2, 2}, (float[]){.40, .50, .45, .55}),
      zode_from_array(2, (uint32_t[]){1, 1}, (float[]){.60}));
  auto network = zn_sequential();
  znnetwork_add_unit(network, dense_layer);
  znnetwork_add_unit(network, hidden_layer);
  auto cost = zn_mse();
  auto tuner = zn_sgd(0.5);

  // Set up learning
  auto learning = zn_supervised_learning(network, cost, tuner);
  zn_dense_train_bias(dense_layer, false);
  zn_dense_train_bias(hidden_layer, false);

  // Train and evaluate
  auto data_sampler = zn_batch_sampler(
      /*x    */ zode_from_array(2, (uint32_t[]){1, 2}, (float[]){.05, .10}),
      /*y_hat*/ zode_from_array(2, (uint32_t[]){1, 2}, (float[]){.01, .99}));

  void *prediction = znnetwork_evaluate(
      network, zode_from_array(2, (uint32_t[]){1, 2}, (float[]){.05, .10}));
  zode_puts(prediction, stdout);


  znlearning_train(learning, data_sampler, 1+10000);

  prediction = znnetwork_evaluate(
      network, zode_from_array(2, (uint32_t[]){1, 2}, (float[]){.05, .10}));
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
  zdelete(sigmoid);

  return 0;
}


inputs = np.random.random((32, 10, 8))//B,T,C
>>> lstm = keras.layers.LSTM(4)
>>> output = lstm(inputs)
>>> output.shape
(32, 4)