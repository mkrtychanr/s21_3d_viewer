#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include "../data_containers/headers/dynamic_string.h"
#include "../data_containers/headers/line_vector.h"
#include "../data_containers/headers/point_vector.h"
#include "../data_containers/headers/polygon_vector.h"

/**
 * @brief Получить точки из файла
 *
 * @param src Путь к файлу
 * @return point_vector* Указатель на динамическую коллекцию с точками
 */
point_vector* get_points_from_file(char* src);

/**
 * @brief Получить связи из файла
 *
 * @param src Путь к файлу
 * @return line_vector* Указатель на динамическую коллекцию со связями
 */
line_vector* get_polygons_from_file(char* src);

/**
 * @brief Распознование точки из строки
 *
 * @param last_stop Строка к распознованию
 * @param str Указатель на динамическую строку для заполнения
 * @return char* Новая строка (сдвиг last_stop)
 */
char* recognize_point(char* last_stop, string* str);

/**
 * @brief Распознование полигона из строки
 *
 * @param last_stop Строка к распознованию
 * @param polygons Указатель на динамическую коллекцию полигонов для заполнения
 * @param out Новая строка (сдвиг last_stop)
 * @return true Можно распозновать дальше
 * @return false Дальше распозновать нет смысла
 */
bool recognize_polygon(char* last_stop, polygon_vector* polygons, char** out);

#endif  // SRC_PARSER_H_