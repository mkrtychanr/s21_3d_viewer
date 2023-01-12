#include "headers/line_vector.h"

void init_line(line_vector* vector) {
  vector->size = 0;
  vector->capacity = 1;
  vector->data = malloc(vector->capacity * sizeof(line));
}

void push_back_line(line_vector* vector, line value) {
  if (vector->size == vector->capacity) {
    vector->capacity *= 2;
    resize_line(vector);
  }
  vector->data[vector->size] = value;
  vector->size++;
}

void resize_line(line_vector* vector) {
  line* temp = malloc(vector->size * sizeof(line));
  for (size_t i = 0; i < vector->size; i++) {
    temp[i] = vector->data[i];
  }
  free(vector->data);
  vector->data = malloc(vector->capacity * sizeof(line));
  for (size_t i = 0; i < vector->size; i++) {
    vector->data[i] = temp[i];
  }
  free(temp);
}

void remove_line(line_vector* vector) { free(vector->data); }