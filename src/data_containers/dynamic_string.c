#include "headers/dynamic_string.h"

void init_string(string* str) {
  str->size = 0;
  str->capacity = 1;
  str->data = malloc((str->capacity + 1) * sizeof(char));
}

void push_back_string(string* str, char value) {
  if (str->size == str->capacity) {
    str->capacity *= 2;
    resize_string(str);
  }
  str->data[str->size] = value;
  str->size++;
  str->data[str->size] = '\0';
}

void resize_string(string* str) {
  char* temp = malloc(str->size * sizeof(char));
  for (size_t i = 0; i < str->size; i++) {
    temp[i] = str->data[i];
  }
  free(str->data);
  str->data = malloc((str->capacity + 1) * sizeof(char));
  for (size_t i = 0; i < str->size; i++) {
    str->data[i] = temp[i];
  }
  str->data[str->size] = '\0';
  free(temp);
}

void remove_string(string* str) {
  if (str->data != nullptr) {
    free(str->data);
    str->data = nullptr;
  }
}
