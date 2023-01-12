#include "parser.h"

#include <stdio.h>
#include <string.h>

point_vector* get_points_from_file(char* src) {
  FILE* object_file = fopen(src, "r");
  if (object_file == nullptr) {
    return nullptr;
  }
  point_vector* points = malloc(sizeof(point_vector));
  init_point(points);
  char* line_from_file = malloc(1024 * sizeof(char));
  while (fgets(line_from_file, 1024, object_file)) {
    char* ptr = line_from_file;
    size_t string_size = strlen(line_from_file);
    if (string_size > 2 && ptr[0] == 'v' && ptr[1] == ' ') {
      point new_point = {0, 0, 0};
      double temp[3] = {0};
      for (int i = 0; i < 3; i++) {
        string raw_point;
        init_string(&raw_point);
        ptr = recognize_point(ptr + 2, &raw_point);
        temp[i] = strtod(raw_point.data, nullptr);
        remove_string(&raw_point);
      }
      new_point.x = temp[0];
      new_point.y = temp[1];
      new_point.z = temp[2];
      push_back_point(points, new_point);
    }
  }
  fclose(object_file);
  free(line_from_file);
  return points;
}

char* recognize_point(char* last_stop, string* str) {
  while (*last_stop != ' ' && *last_stop != '\n') {
    push_back_string(str, *last_stop);
    last_stop++;
  }
  return last_stop - 1;
}

line_vector* get_polygons_from_file(char* src) {
  FILE* object_file = fopen(src, "r");
  if (object_file == nullptr) {
    return nullptr;
  }
  line_vector* lines = malloc(sizeof(line_vector));
  init_line(lines);
  char* line_from_file = malloc(1024 * sizeof(char));
  while (fgets(line_from_file, 1024, object_file)) {
    polygon_vector polygons;
    init_polygon(&polygons);
    char* ptr = line_from_file + 2;
    size_t string_size = strlen(ptr);
    if (string_size > 2 && line_from_file[0] == 'f' &&
        line_from_file[1] == ' ') {
      while (recognize_polygon(ptr, &polygons, &ptr)) {
      }
      for (size_t i = 0; i < polygons.size - 1; i++) {
        line temp = {polygons.data[i], polygons.data[i + 1]};
        push_back_line(lines, temp);
      }
      line temp = {polygons.data[polygons.size - 1], polygons.data[0]};
      push_back_line(lines, temp);
    }
    remove_polygon(&polygons);
  }
  fclose(object_file);
  free(line_from_file);
  return lines;
}

bool recognize_polygon(char* last_stop, polygon_vector* polygons, char** out) {
  string number;
  init_string(&number);
  bool digit_detected = false;
  while (*last_stop == ' ') {
    last_stop++;
  }
  if (*last_stop == '\n' || *last_stop == '\0') {
    return false;
  }
  while ('0' <= *last_stop && *last_stop <= '9') {
    digit_detected = true;
    push_back_string(&number, *last_stop);
    last_stop++;
  }
  if (digit_detected) {
    push_back_polygon(polygons, atoi(number.data));
  }
  remove_string(&number);
  if (*last_stop == '/') {
    while (*last_stop != ' ' && *last_stop != '\0' && *last_stop != '\n') {
      ++last_stop;
    }
  }
  *out = last_stop;
  return true;
}
