#include "../../include/volume/volume.r.h"
#include <assert.h>
#include <zobject.h>
#include <zobject.r.h>

float* znvolume_at(znvolume *volume, zsize *idx) {
  znvolume_class *class = (znvolume_class *)zclassof((zobject *)volume);
  assert((*class).at);
  return (*class).at(volume, idx);
}
void znvolume_reshape(znvolume *volume, zsize *shape) {
  znvolume_class *class = (znvolume_class *)zclassof((zobject *)volume);
  assert((*class).reshape);
  return (*class).reshape(volume, shape);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNVolume,znvolume, Z_SELECTOR_PAIR(znvolume, at),
                           Z_SELECTOR_PAIR(znvolume, reshape))

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNVolume, ZNComponent,
                             znvolume_class_constructor, NULL)
