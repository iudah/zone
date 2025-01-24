#include "../../include/volume/volume.r.h"
#include <assert.h>
#include <stdint.h>
#include <zobject.h>
#include <zobject.r.h>
#include <zode.h>

static znvolume *znvolume_constructor(znvolume *volume, va_list *argp) {

  auto rank = va_arg(*argp, int);
  auto shape = va_arg(*argp, uint32_t *);

  volume->tensor = zode_create_tensor(rank, shape);

  return volume;
}
static znvolume *znvolume_destructor(znvolume *volume) {

  zode_destroy(volume->tensor);

  return volume;
}

static char *describe() {
  return "Volume with shape: ";
  // + std::to_string(zode_tensor_rows(tensor)) +
  //     "x" + std::to_string(zode_tensor_cols(tensor));
}

float znvolume_at(znvolume *volume, int32_t *idx) {
  float result;
  if (zode_get_element(volume->tensor, idx, &result)) {
    LOG_ERROR("Failed to get element.");
  }
  return result;
}
void znvolume_reshape(znvolume *volume, uint8_t rank, uint32_t *shape) {
  return zode_reshape(volume->tensor, rank, shape);
}

Z_DEFINE_CLASS_CONSTRUCTOR(ZNVolume, znvolume, )

Z_INIT_CLASS_WITH_PRIORITIES(131, ZNVolume, ZNComponent,
                             znvolume_class_constructor, zctor,
                             znvolume_constructor, NULL)
