typedef struct dynamic_string string;

#ifndef SRC_DATA_CONTAINERS_HEADERS_DYNAMIC_STRING_H_
#define SRC_DATA_CONTAINERS_HEADERS_DYNAMIC_STRING_H_

#include "common.h"

/**
 * @brief Структура для динамической структуры
 *
 */
struct dynamic_string {
  char* data;
  size_t size;
  size_t capacity;
};

/**
 * @brief Инициализатор динамической строки
 *
 * @param str Указатель на структуру строки
 */
void init_string(string* str);

/**
 * @brief Добавление нового символа в динамическую строку
 *
 * @param str Указатель на структуру строки
 * @param value Символ к добавлению
 */
void push_back_string(string* str, char value);

/**
 * @brief Резайз строки в случае переполнения
 *
 * @param str Указатель на структуру строки
 */
void resize_string(string* str);

/**
 * @brief Уничтожитель строки
 *
 * @param str Указатель на структуру строки
 */
void remove_string(string* str);

#endif  // SRC_DATA_CONTAINERS_HEADERS_DYNAMIC_STRING_H_