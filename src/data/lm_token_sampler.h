#ifndef LM_TOKEN_SAMPLER_H
#define LM_TOKEN_SAMPLER_H

#include <zobject.h>

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS_TYPE(ZNLMTokenSampler, znlmtokensampler)

void *zn_lm_token_sampler(void *input, uint32_t context_size,
                          uint32_t token_axis);

#ifdef __cplusplus
}
#endif
#endif