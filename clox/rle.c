#include <stdio.h>

#include "memory.h"
#include "rle.h"

void initValueArray(RLEArray *array) {
  array->values = NULL;
  array->capacity = 0;
  array->count = 0;
}

void writeValueArray(RLEArray *array, uint8_t value) {
  if (array->capacity < array->count + 1) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->values =
        GROW_ARRAY(uint8_t, array->values, oldCapacity, array->capacity);
  }

  if (array->count == 0 || array->values[array->count - 1] != value) {
    array->values[array->count++] = 1;
    array->values[array->count++] = value;
  } else {
    array->values[array->count - 2] += 1;
  }
}

uint8_t getRLEArray(RLEArray *array, uint8_t index) {
  int current_position = 0;
  for (int i = 0, j = array->count / 2; i != j; ++i) {
    if (current_position + array->values[i * 2] - 1 < index) {
      current_position += array->values[i * 2];
      continue;
    }
    return array->values[i * 2 + 1];
  }
  return '\0';
}

void freeValueArray(RLEArray *array) {
  FREE_ARRAY(uint8_t, array->values, array->capacity);
  initValueArray(array);
}
