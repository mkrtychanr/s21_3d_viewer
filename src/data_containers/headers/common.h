typedef struct point point;
typedef struct line line;

#define false 0
#define true 1
#define bool int
#define polygon int
#ifndef SRC_DATA_CONTAINERS_HEADERS_COMMON_H_
#define SRC_DATA_CONTAINERS_HEADERS_COMMON_H_

#include <stdlib.h>

#define nullptr NULL

/**
 * @brief Стркутура для точки
 *
 */
struct point {
  double x;
  double y;
  double z;
};

/**
 * @brief Структура для связи
 *
 */
struct line {
  size_t from;
  size_t to;
};

#endif  // SRC_DATA_CONTAINERS_HEADERS_COMMON_H_