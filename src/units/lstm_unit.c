#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>
#include <zot.h>

#include "lstmunit.r.h"
#include "unit.h"

void *zn_lstm(uint64_t out_dim, uint64_t in_dim, uint64_t hidden_dim,
              void *gate_activator, void *state_activator) {
  return znew(ZNLSTMUnit, out_dim, in_dim, hidden_dim, gate_activator,
              state_activator, nullptr);
}

static void zn_lstm_train(void *var_node, bool whether_to_train) {
  if (!whether_to_train) {
    zode_stop_gradient(var_node);
  } else {
    zode_continue_gradient(var_node);
  }
}

// void zn_lstm_train_weight(void *lstm, bool whether_to_train_weight) {
//   return zn_lstm_train(((znlstmunit *)lstm)->weights,
//                         whether_to_train_weight);
// }
// void zn_lstm_train_bias(void *lstm, bool whether_to_train_bias) {
//   return zn_lstm_train(((znlstmunit *)lstm)->biases, whether_to_train_bias);
// }

znlstmunit *znlstmunit_constructor(znlstmunit *lstmunit, va_list *argp) {
  lstmunit->num_units = va_arg(*argp, uint64_t);
  auto num_in = va_arg(*argp, uint64_t);
  auto num_hidden = lstmunit->num_hidden_units = va_arg(*argp, uint64_t);
  lstmunit->gate_activation = va_arg(*argp, zntrigger *);
  lstmunit->state_activation = va_arg(*argp, zntrigger *);

  lstmunit->hidden_vector =
      zode_random(2, (uint32_t[]){num_hidden, num_hidden});

  lstmunit->input_gate_weights =
      zode_random(2, (uint32_t[]){num_hidden, num_hidden});
  lstmunit->forget_gate_weights =
      zode_random(2, (uint32_t[]){num_hidden, num_hidden});
  lstmunit->cell_candidate_weights =
      zode_random(2, (uint32_t[]){num_hidden, num_hidden});
  lstmunit->output_gate_weights =
      zode_random(2, (uint32_t[]){num_hidden, num_hidden});

#ifdef UNIQUE_RECURRENT_WEIGHTS

  lstmunit->input_gate_recurrent_weights =
      zode_random(2, (uint32_t[]){num_hidden, num_hidden});
  lstmunit->forget_gate_recurrent_weights =
      zode_random(2, (uint32_t[]){num_hidden, num_hidden});
  lstmunit->cell_candidate_recurrent_weights =
      zode_random(2, (uint32_t[]){num_hidden, num_hidden});
  lstmunit->output_gate_recurrent_weights =
      zode_random(2, (uint32_t[]){num_hidden, num_hidden});

#else

  lstmunit->input_gate_recurrent_weights = lstmunit->input_gate_weights;
  lstmunit->forget_gate_recurrent_weights = lstmunit->forget_gate_weights;
  lstmunit->cell_candidate_recurrent_weights = lstmunit->cell_candidate_weights;
  lstmunit->output_gate_recurrent_weights = lstmunit->output_gate_weights;

#endif

  lstmunit->input_gate_bias = zode_random(2, (uint32_t[]){num_hidden, 1});
  lstmunit->forget_gate_bias = zode_random(2, (uint32_t[]){num_hidden, 1});
  lstmunit->cell_candidate_bias = zode_random(2, (uint32_t[]){num_hidden, 1});
  lstmunit->output_gate_bias = zode_random(2, (uint32_t[]){num_hidden, 1});

  return lstmunit;
}

struct gate_state {
  void **gate;
  void *input;
  void *hidden_vector;
  void *activation;
  void *weight;
  void *r_weight;
  void *bias;
};

static void *compute_gate(void *ptr) {
  struct gate_state *gate_state = ptr;

  *gate_state->gate = zntrigger_trigger(
      gate_state->activation,
      zode_add(
          zode_matmul(gate_state->input, gate_state->weight),
          zode_add(zode_matmul(gate_state->hidden_vector, gate_state->r_weight),
                   gate_state->bias)));

  return NULL;
}

static void *compute(znlstmunit *lstmunit, void *input) {
  void *i_gate, *f_gate, *c_candidate, *o_gate;
  pthread_t input_thread, forget_thread, cell_thread, output_thread;

  int i_ret = zthread_create(
      &input_thread, NULL, compute_gate,
      (struct gate_state[1]){
          &i_gate, input, lstmunit->hidden_vector, lstmunit->gate_activation,
          lstmunit->input_gate_weights, lstmunit->input_gate_recurrent_weights,
          lstmunit->input_gate_bias});
  int f_ret = zthread_create(
      &forget_thread, NULL, compute_gate,
      (struct gate_state[1]){
          &f_gate, input, lstmunit->hidden_vector, lstmunit->gate_activation,
          lstmunit->forget_gate_weights,
          lstmunit->forget_gate_recurrent_weights, lstmunit->forget_gate_bias});
  int c_ret = zthread_create(
      &cell_thread, NULL, compute_gate,
      (struct gate_state[1]){&c_candidate, input, lstmunit->hidden_vector,
                             lstmunit->state_activation,
                             lstmunit->cell_candidate_weights,
                             lstmunit->cell_candidate_recurrent_weights,
                             lstmunit->cell_candidate_bias});
  int o_ret = zthread_create(
      &forget_thread, NULL, compute_gate,
      (struct gate_state[1]){
          &o_gate, input, lstmunit->hidden_vector, lstmunit->gate_activation,
          lstmunit->output_gate_weights,
          lstmunit->output_gate_recurrent_weights, lstmunit->output_gate_bias});

  pthread_join(input_thread, NULL);
  pthread_join(forget_thread, NULL);
  pthread_join(cell_thread, NULL);
  pthread_join(output_thread, NULL);

  lstmunit->cell_state = zode_add(zode_multiply(f_gate, lstmunit->cell_state),
                                  zode_multiply(i_gate, c_candidate));
  lstmunit->hidden_vector =
      zode_multiply(o_gate, zntrigger_trigger(lstmunit->state_activation,
                                              lstmunit->cell_state));

  return o_gate;
}

static void initialize(znlstmunit *lstmunit) {
  printf("LSTMUnit initialized with %" PRIu32 " units.\n", lstmunit->num_units);
}

static char *describe(znlstmunit *lstmunit) {
  ZN_QUICK_DESCRIBE(buffer, "LSTMUnit with %" PRIu32 " units.",
                    lstmunit->num_units);
  return buffer;
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNUnit, znunit, )

Z_INIT_CLASS_WITH_PRIORITIES(134, ZNLSTMUnit, ZNUnit, NULL, zctor,
                             znlstmunit_constructor, znunit_compute, compute,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe, NULL)
