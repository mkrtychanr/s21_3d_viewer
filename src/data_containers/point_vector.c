#include "headers/point_vector.h"

void init_point(point_vector* vector) {
  vector->size = 0;
  vector->capacity = 1;
  vector->data = malloc(vector->capacity * sizeof(point));
}

void push_back_point(point_vector* vector, point value) {
  if (vector->size == vector->capacity) {
    vector->capacity *= 2;
    resize_point(vector);
  }
  vector->data[vector->size] = value;
  vector->size++;
}

void resize_point(point_vector* vector) {
  point* temp = malloc(vector->size * sizeof(point));
  for (size_t i = 0; i < vector->size; i++) {
    temp[i] = vector->data[i];
  }
  free(vector->data);
  vector->data = malloc(vector->capacity * sizeof(point));
  for (size_t i = 0; i < vector->size; i++) {
    vector->data[i] = temp[i];
  }
  free(temp);
}

void remove_point(point_vector* vector) { free(vector->data); }

point_vector* copy_point(point_vector* vector) {
  point_vector* result = malloc(sizeof(point_vector));
  init_point(result);
  for (size_t i = 0; i < vector->size; i++) {
    push_back_point(result, vector->data[i]);
  }
  return result;
}
