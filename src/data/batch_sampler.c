#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>
#include <zot.h>

#include "batch_sampler.r.h"

static znbatchsampler *batchsampler_constructor(znbatchsampler *batch_sampler,
                                                va_list *argp) {
  batch_sampler->inputs = va_arg(*argp, void *);
  if (!batch_sampler->inputs) {
    LOG_ERROR("ZNBatchSampler expects at least input tensor.");
    return NULL;
  } else {
    batch_sampler->labels = va_arg(*argp, void *);
  }

  return batch_sampler;
}

static void **sample_batch(znbatchsampler *sampler, zsize batch_size,
                           zsize *n_batch) {
  printf("Sampling a batch of size: %" PRIu64 "\n", batch_size);
  auto sample_length = zode_shape(sampler->inputs, (uint32_t[256]){1})[0];
  *n_batch = (sample_length + batch_size - 1) / batch_size;

  void **batches = zcalloc(*n_batch * 2, sizeof(void *));
  for (int i = 0; i < *n_batch; i++) {
    batches[i * 2] = zode_slice(
        sampler->inputs, 2,
        (int32_t *[]){(int32_t[]){i * batch_size,
                                  *n_batch == (i + 1) ? sample_length
                                                      : ((i + 1) * batch_size),
                                  1},
                      ELLIPSIS});

    batches[i * 2 + 1] =
        sampler->labels != NULL
            ? zode_slice(sampler->labels, 2,
                         (int32_t *[]){(int32_t[]){i * batch_size,
                                                   *n_batch == (i + 1)
                                                       ? sample_length
                                                       : ((i + 1) * batch_size),
                                                   1},
                                       ELLIPSIS})
            : NULL;
  }

  return batches;
}

static void initialize(znbatchsampler *sampler) {
  printf("BatchSampler initialized.\n");
}

static char *describe() { return "BatchSampler for data batching."; }

Z_DEFINE_CLASS_CONSTRUCTOR(ZNBatchSampler, znbatchsampler, )

Z_INIT_CLASS_WITH_PRIORITIES(133, ZNBatchSampler, ZNSampler, NULL, zctor,
                             batchsampler_constructor, zncomponent_initialize,
                             initialize, zncomponent_describe, describe,
                             znsampler_sample_batch, sample_batch, NULL)
