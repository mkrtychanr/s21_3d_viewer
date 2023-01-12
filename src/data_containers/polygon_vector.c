#include "headers/polygon_vector.h"

void init_polygon(polygon_vector* vector) {
  vector->size = 0;
  vector->capacity = 1;
  vector->data = malloc(vector->capacity * sizeof(polygon));
}

void push_back_polygon(polygon_vector* vector, polygon value) {
  if (vector->size == vector->capacity) {
    vector->capacity *= 2;
    resize_polygon(vector);
  }
  vector->data[vector->size] = value;
  vector->size++;
}

void resize_polygon(polygon_vector* vector) {
  polygon* temp = malloc(vector->size * sizeof(polygon));
  for (size_t i = 0; i < vector->size; i++) {
    temp[i] = vector->data[i];
  }
  free(vector->data);
  vector->data = malloc(vector->capacity * sizeof(polygon));
  for (size_t i = 0; i < vector->size; i++) {
    vector->data[i] = temp[i];
  }
  free(temp);
}

void remove_polygon(polygon_vector* vector) { free(vector->data); }