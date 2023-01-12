typedef struct polygon_vector polygon_vector;

#ifndef SRC_DATA_CONTAINERS_HEADERS_POLYGON_VECTOR_H_
#define SRC_DATA_CONTAINERS_HEADERS_POLYGON_VECTOR_H_

#include "common.h"

/**
 * @brief Структура динамической коллекции полигонов
 *
 */
struct polygon_vector {
  polygon* data;
  size_t size;
  size_t capacity;
};

/**
 * @brief Инициализатор динамической коллекции точек
 *
 * @param vector Указатель на структуру полигонов
 */
void init_polygon(polygon_vector* vector);

/**
 * @brief Добавление нового полигона в динамическую коллецию
 *
 * @param vector Указатель на структуру полигонов
 * @param value Полигон к добавлению
 */
void push_back_polygon(polygon_vector* vector, polygon value);

/**
 * @brief Ресайз динамической коллекции полигонов
 *
 * @param vector Указатель на структуру полигонов
 */
void resize_polygon(polygon_vector* vector);

/**
 * @brief Очистка динамической коллекции полигонов
 *
 * @param vector Указатель на структуру полигонов
 */
void remove_polygon(polygon_vector* vector);

#endif  // SRC_DATA_CONTAINERS_HEADERS_POINT_VECTOR_H_