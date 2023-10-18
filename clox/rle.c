#include <stdio.h>

#include "memory.h"
#include "rle.h"

void initRLEArray(RLEArray *array) {
  array->values = NULL;
  array->capacity = 0;
  array->count = 0;
}

void writeRLEArray(RLEArray *array, int value) {
  if (array->capacity < array->count + 1) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->values =
        GROW_ARRAY(int, array->values, oldCapacity, array->capacity);
  }

  if (array->count == 0 || array->values[array->count - 1] != value) {
    array->values[array->count++] = 1;
    array->values[array->count++] = value;
  } else {
    array->values[array->count - 2] += 1;
  }
}

int getRLEArray(RLEArray *array, int index) {
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

void freeRLEArray(RLEArray *array) {
  FREE_ARRAY(int, array->values, array->capacity);
  initRLEArray(array);
}
