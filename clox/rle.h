#ifndef rle_clox_h
#define rle_clox_h

#include "common.h"

typedef struct {
  int capacity;
  int count;
  int *values;
} RLEArray;

void initRLEArray(RLEArray *array);
void writeRLEArray(RLEArray *array, int value);
int getRLEArray(RLEArray *array, int index);
void freeRLEArray(RLEArray *array);

#endif