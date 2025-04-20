#ifndef LSTMUNIT_R_H
#define LSTMUNIT_R_H

#include <zobject.r.h>

#include "../triggers/trigger.h"
#include "denseunit.h"
#include "lstmunit.h"
#include "unit.r.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(znunit, ZNLSTMUnit, znlstmunit,
                /*members*/
                zntrigger *gate_activation;
                zntrigger * state_activation;

                void *hidden_vector; void *cell_state;

                void *input_gate_weights; void *forget_gate_weights;
                void *cell_candidate_weights; void *output_gate_weights;

                void *input_gate_recurrent_weights;
                void *forget_gate_recurrent_weights;
                void *cell_candidate_recurrent_weights;
                void *output_gate_recurrent_weights;

                void *input_gate_bias; void *forget_gate_bias;
                void *cell_candidate_bias; void *output_gate_bias;

                uint32_t num_units; uint32_t num_hidden_units;,
                /*methods*/)

#ifdef __cplusplus
}
#endif
#endif