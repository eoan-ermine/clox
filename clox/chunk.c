#include "chunk.h"
#include "memory.h"

void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  initRLEArray(&chunk->lines);
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  initRLEArray(&chunk->lines);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code =
        GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  writeRLEArray(&chunk->lines, line);
  chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

void writeConstant(Chunk *chunk, Value value, int line) {
  int constant_idx = addConstant(chunk, value);

  if (constant_idx <= 255) {
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, constant_idx, line);
  } else {
    writeChunk(chunk, OP_CONSTANT_LONG, line);
    writeChunk(chunk, ((unsigned int)constant_idx >> (2 << 3)) & 0xff, line);
    writeChunk(chunk, ((unsigned int)constant_idx >> (1 << 3)) & 0xff, line);
    writeChunk(chunk, ((unsigned int)constant_idx >> (0 << 3)) & 0xff, line);
  }
}

int getLine(Chunk *chunk, int instr_idx) {
  return getRLEArray(&chunk->lines, instr_idx);
}