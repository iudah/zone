#ifndef LSTMUNIT_H
#define LSTMUNIT_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNLSTMUnit, znlstmunit)

void *zn_lstm(uint64_t out_dim, uint64_t in_dim, uint64_t hidden_dim,
              void *gate_activator, void *state_activator);
// void zn_lstm_train_weight(void *lstm, bool whether_to_train_weight);
// void zn_lstm_train_bias(void *lstm, bool whether_to_train_bias);

#ifdef __cplusplus
}
#endif
#endif