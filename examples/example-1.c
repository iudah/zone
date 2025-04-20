
#ifndef INSTALL_DIR
#define INSTALL_DIR "/mnt/sdcard/Jay/Projects/xab_laud_ubject/zone/"
#endif

#include "../src/cost/cross_entropy_cost.h"
#include "../src/cost/mse_cost.h"
#include "../src/data/lm_token_sampler.h"
#include "../src/network/network.h"
#include "../src/network/sequential_network.h"
#include "../src/training/learning.h"
#include "../src/training/supervised_learning.h"
#include "../src/triggers/sigmoidtrigger.h"
#include "../src/tuning/sgd_tuner.h"
#include "../src/units/denseunit.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <zobject.h>
#include <zode.h>
#include <zot.h>

void *zn_bigram(uint64_t vocab_size);

void insert_char(char *set, uint64_t *count, char c) {
  if (*count == 0) {
    set[(*count)++] = c;
    set[*count] = 0;
    return;
  }
  if (c > set[*count - 1]) {
    set[(*count)++] = c;
    set[*count] = 0;
    return;
  }
  if (c == set[*count - 1]) {
    return;
  }
  if (c == *set)
    return;
  volatile uint64_t i = *count - 1;
  if (c > *set) {
    while (i && c < set[i]) {
      i -= 1;
    }
    if (c == set[i])
      return;

    i = *count - 1;
  }
  while (i && c < set[i]) {
    set[i + 1] = set[i];
    i -= 1;
  }
  if (c < *set) {
    set[1] = set[0];
    *set = c;
  } else
    set[i + 1] = c;
  (*count)++;

  set[*count] = 0;
}

float *encode_text(char *code, char *text) {
  uint64_t text_length = strlen(text);
  float *coded = zcalloc(text_length, sizeof(*coded));
  char *text_ptr = text, *code_ptr;
  float *coded_ptr = coded;
  while (*text_ptr) {
    code_ptr = code;
    *coded_ptr = 0;
    while (*code_ptr != *text_ptr) {
      (*coded_ptr)++;
      code_ptr++;
    }
    text_ptr++;
    coded_ptr++;
  }
  return coded;
}

char *decode_floats(char *code, float *floats, uint64_t float_length) {
  uint64_t text_length = float_length;
  char *text = zcalloc((text_length + 1), sizeof(*text));
  char *text_ptr = text;
  volatile float *coded_ptr = floats;
  while (float_length) {
    *text_ptr = code[(uint64_t)*coded_ptr];
    float_length--;
    text_ptr++;
    coded_ptr++;
  }
  *text_ptr = 0;
  return text;
}

int main() {
  /// load sample text
  FILE *sample_text = fopen(INSTALL_DIR "/assets/sample_text.txt", "r");
  if (!sample_text) {
    printf("Sample text not found.");
    return 1;
  }
  struct stat file_status;
  fstat(fileno(sample_text), &file_status);
  char *buffer = zmalloc(file_status.st_size + 1);
  fread(buffer, sizeof(*buffer), file_status.st_size, sample_text);
  fclose(sample_text);

  buffer[file_status.st_size] = 0;
  printf("%s\n", buffer);

  // determine unique characters
  char unique_characters[250];
  uint64_t no_unique_characters = 0;

  char *c = buffer;
  while (*c) {
    insert_char(unique_characters, &no_unique_characters, *c);
    c++;
  }
  unique_characters[no_unique_characters] = 0;

  printf("Unique characters: `%s\nNumber of unique characters: %" PRIu64 "`\n",
         unique_characters, no_unique_characters);

  uint64_t vocab_size = no_unique_characters;

  // encode text
  float *short_encode = encode_text(unique_characters, "sally");
  char *short_decode = decode_floats(unique_characters, short_encode, 5);

  printf("Short encode: ");
  for (int i = 0; i < 5; i++) {
    printf("%g ", short_encode[i]);
  }
  printf(" => %s\n", short_decode);

  float *sample_text_float = encode_text(unique_characters, buffer);
  buffer = NULL;

  // split
  uint64_t context_size = 8;
  uint64_t train_len = (uint64_t)(file_status.st_size * 0.9);
  uint64_t validate_len = file_status.st_size - train_len;
  float *train = sample_text_float;
  float *validate = sample_text_float + (uint64_t)(train_len);

  auto training_sampler = zn_lm_token_sampler(
      /*x    */ zode_from_array(2, (uint32_t[]){1, train_len}, train),
      context_size, 1);
  auto validation_sampler = zn_lm_token_sampler(
      /*x    */ zode_from_array(2, (uint32_t[]){1, validate_len}, validate),
      context_size, 1);

  void *bigram = zn_bigram(vocab_size);
  auto network = zn_sequential();
  znnetwork_add_unit(network, bigram);

  auto learning =
      zn_supervised_learning(network, zn_cross_entropy(2), zn_sgd(0.3));

  void *prediction = znnetwork_evaluate(
      network, zode_from_array(2, (uint32_t[]){1, 5}, short_encode));
  // zode_puts(prediction, stdout);
}
