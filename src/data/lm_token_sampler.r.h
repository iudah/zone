#ifndef LM_TOKEN_SAMPLER_R_H
#define LM_TOKEN_SAMPLER_R_H

#include <zobject.r.h>

#include "lm_token_sampler.h"
#include "sampler.r.h"

#ifdef __cplusplus
extern "C" {
#endif

Z_DECLARE_CLASS(znsampler, ZNLMTokenSampler, znlmtokensampler,
                /*members*/ void *inputs;
                uint32_t context_size; 
                uint8_t token_axis;,
                /*methods*/
)

#ifdef __cplusplus
}
#endif
#endif