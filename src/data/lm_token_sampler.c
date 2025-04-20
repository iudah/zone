#include <assert.h>
#include <pcg_variants.h>
#include <stdarg.h>
#include <string.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>
#include <zot.h>

#include "lm_token_sampler.r.h"

void *zn_lm_token_sampler(void *input, uint32_t context_size,
                          uint32_t token_axis) {
  return znew(ZNLMTokenSampler,
              /*x    */ input, context_size, token_axis, NULL);
}

static znlmtokensampler *
lmtokensampler_constructor(znlmtokensampler *lm_token_sampler, va_list *argp) {
  lm_token_sampler->inputs = va_arg(*argp, void *);
  if (!lm_token_sampler->inputs) {
    LOG_ERROR("ZNLMTokenSampler expects an input tensor.");
    return NULL;
  } else {
    lm_token_sampler->context_size = va_arg(*argp, uint32_t);
    lm_token_sampler->token_axis = va_arg(*argp, uint32_t);
  }

  if (lm_token_sampler->context_size < 1) {
    LOG_ERROR("ZNLMTokenSampler expects context size >= 1.");
    return NULL;
  }

  if ((lm_token_sampler->context_size + 1) >
      zode_shape(lm_token_sampler->inputs,
                 (uint32_t[256]){})[lm_token_sampler->token_axis]) {
    LOG_ERROR("ZNLMTokenSampler expects an input tensor have at least context "
              "size + 1 data points.");
    return NULL;
  }

  return lm_token_sampler;
}

static void **sample_batch(znlmtokensampler *sampler, zsize batch_size,
                           zsize *n_batch) {
  // determine length of sampler
  auto tokens_tnsr_shape = zode_shape(sampler->inputs, (uint32_t[256]){});
  auto token_axis = sampler->token_axis;
  auto tokens_length = tokens_tnsr_shape[token_axis];
  auto data_rank = zode_rank(sampler->inputs);

  auto context_size = sampler->context_size;
  if (batch_size * context_size > tokens_length &&
      (context_size + 1) < tokens_length) {
    batch_size = tokens_length / context_size;
  } else {
    LOG_ERROR("Tokens are not enough to complete a context.");
    return NULL;
  }
  uint64_t token_limit = tokens_length - batch_size * context_size - 1;

  auto nbatches = *n_batch = token_limit;

  auto rank = data_rank + 1;
  uint32_t shape[rank];
  memcpy(shape, tokens_tnsr_shape, token_axis * sizeof(*shape));
  int32_t *slice_triples[data_rank];
  if (data_rank - token_axis > 1) {
    memcpy(shape + token_axis + 1, tokens_tnsr_shape + token_axis,
           (data_rank - token_axis) * sizeof(*shape));
    memset(slice_triples + token_axis, 0,
           sizeof(*slice_triples) * (data_rank - token_axis));
    slice_triples[token_axis + 1] = ELLIPSIS;
  }
  
  shape[token_axis] = batch_size;
  shape[token_axis + 1] = context_size;

  for (int32_t i = 0; i < token_axis; i++) {
    slice_triples[i] = NULL;
  }

  void **batches = zcalloc(*n_batch * 2, sizeof(void *));
  for (int j = 0; j < *n_batch; j++) {

    uint32_t idx = token_limit * pcg32_random() / UINT32_MAX;

    slice_triples[token_axis] =
        (int32_t[]){idx * batch_size * context_size,
                    ((idx + 1) * batch_size * context_size), 1};

    batches[j * 2] = zode_slice(sampler->inputs, token_axis + 2, slice_triples);
    zode_reshape(batches[j * 2], rank, shape);

    slice_triples[token_axis] =
        (int32_t[]){idx * batch_size * context_size + 1,
                    ((idx + 1) * batch_size * context_size + 1), 1};

    batches[j * 2 + 1] =
        zode_slice(sampler->inputs, token_axis + 2, slice_triples);
    zode_reshape(batches[j * 2 + 1], rank, shape);
  }

  return batches;
}

static void initialize(znlmtokensampler *sampler) {
  printf("LMTokenSampler initialized.\n");
}

static char *describe() { return "LMTokenSampler for data batching."; }

Z_DEFINE_CLASS_CONSTRUCTOR(ZNLMTokenSampler, znlmtokensampler, )

Z_INIT_CLASS_WITH_PRIORITIES(133, ZNLMTokenSampler, ZNSampler, NULL, zctor,
                             lmtokensampler_constructor, zncomponent_initialize,
                             initialize, zncomponent_describe, describe,
                             znsampler_sample_batch, sample_batch, NULL)
