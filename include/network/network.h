#ifndef NETWORK_H
#define NETWORK_H

#include "../units/unit.h"
#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNNetwork, znnetwork)

void znnetwork_add_unit(znnetwork *network, znunit *unit);
void znnetwork_evaluate(znnetwork *network);
void znnetwork_train(znnetwork *network);

#ifdef __cplusplus
}
#endif
#endif