#include "../../include/data/sampler.r.h"

#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

void **znsampler_sample_batch(void *sampler, zsize batch_size, zsize *n_batch) {
  znsampler_class *class = (znsampler_class *)zclassof((zobject *)sampler);
  assert((*class).sample_batch);
  return (*class).sample_batch(sampler, batch_size, n_batch);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNSampler, znsampler,
                           Z_SELECTOR_PAIR(znsampler, sample_batch))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNSampler, ZNComponent,
                             znsampler_class_constructor, NULL)
