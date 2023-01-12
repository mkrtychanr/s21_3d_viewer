typedef struct point_vector point_vector;

#ifndef SRC_DATA_CONTAINERS_HEADERS_POINT_VECTOR_H_
#define SRC_DATA_CONTAINERS_HEADERS_POINT_VECTOR_H_

#include "common.h"

/**
 * @brief Структура динамической коллекции точек
 *
 */
struct point_vector {
  point* data;
  size_t size;
  size_t capacity;
};

/**
 * @brief Инициализатор динамической коллекции точек
 *
 * @param vector Указатель на структуру точек
 */
void init_point(point_vector* vector);

/**
 * @brief Добавление новой точки в динамическую коллецию
 *
 * @param vector Указатель на структуру точек
 * @param value Точка к добавлению
 */
void push_back_point(point_vector* vector, point value);

/**
 * @brief Ресайз динамической коллекции точек
 *
 * @param vector Указатель на структуру точек
 */
void resize_point(point_vector* vector);

/**
 * @brief Очистка динамической коллекции точек
 *
 * @param vector
 */
void remove_point(point_vector* vector);

/**
 * @brief Глубокое копирование динамической коллекции точек
 *
 * @param vector Указатель на структуру точек
 * @return point_vector* Указатель на новую коллекцию
 */
point_vector* copy_point(point_vector* vector);

#endif  // SRC_DATA_CONTAINERS_HEADERS_POINT_VECTOR_H_