typedef struct line_vector line_vector;

#ifndef SRC_DATA_CONTAINERS_HEADERS_LINE_VECTOR_H_
#define SRC_DATA_CONTAINERS_HEADERS_LINE_VECTOR_H_

#include "common.h"

/**
 * @brief Стуктура динамической коллекции связей
 *
 */
struct line_vector {
  line* data;
  size_t size;
  size_t capacity;
};

/**
 * @brief Инициализатор динамической коллекции связей
 *
 * @param vector Указатель на структуру связей
 */
void init_line(line_vector* vector);

/**
 * @brief Добавление новой связи в динамическую коллецию
 *
 * @param vector Указатель на структуру связей
 * @param value Связь к добавлению
 */
void push_back_line(line_vector* vector, line value);

/**
 * @brief Ресайз динамической коллекции связей
 *
 * @param vector Указатель на структуру связей
 */
void resize_line(line_vector* vector);

/**
 * @brief Очистка динамической коллекции связей
 *
 * @param vector Указатель на структуру связей
 */
void remove_line(line_vector* vector);

#endif  // SRC_DATA_CONTAINERS_HEADERS_LINE_VECTOR_H_