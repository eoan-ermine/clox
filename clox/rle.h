#ifndef rle_clox_h
#define rle_clox_h

#include "common.h"

typedef struct {
  int capacity;
  int count;
  uint8_t *values;
} RLEArray;

void initRLEArray(RLEArray *array);
void writeRLEArray(RLEArray *array, uint8_t value);
uint8_t getRLEArray(RLEArray *array, uint8_t index);
void freeRLEArray(RLEArray *array);

#endif