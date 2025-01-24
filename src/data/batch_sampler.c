#include "../../include/data/batch_sampler.r.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

static znbatchsampler *batchsampler_constructor(znbatchsampler *batch_sampler,
                                                void **dataset) {
  batch_sampler->data = dataset;
  return batch_sampler;
}

static void **sample_batch(znbatchsampler *sampler, zsize batch_size,
                           zsize *n_batch) {
  printf("Sampling a batch of size: %" PRIu64 "\n", batch_size);
  *n_batch = 1;

  //  std::vector<zode_tensor*> batch;
  //         for (int i = 0; i < batchSize && i < data.size(); ++i) {
  //             batch.push_back(data[i]);
  //         }

  return zcalloc(*n_batch, sizeof(void *)); // Placeholder for batch sampling
}

static void initialize(znbatchsampler *sampler) {
  // return "BatchSampler with " + std::to_string(data.size()) + " samples.";

  printf("BatchSampler initialized.\n");
}

static char *describe() { return "BatchSampler for data batching."; }

Z_DEFINE_CLASS_CONSTRUCTOR(ZNBatchSampler, znbatchsampler, )

Z_INIT_CLASS_WITH_PRIORITIES(133, ZNBatchSampler, ZNSampler, NULL,
                             zncomponent_initialize, initialize,
                             zncomponent_describe, describe,
                             znsampler_sample_batch, sample_batch, NULL)
