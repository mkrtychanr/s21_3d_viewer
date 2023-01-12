#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser/parser.h"
#include "data_containers/headers/point_vector.h"

START_TEST(test_points) {
    get_points_from_file("notExistFile");
    point_vector* result = get_points_from_file("test.obj");
    ck_assert_int_eq(result -> size, 4);
    point_vector* new_result = copy_point(result);
    remove_point(result);
    remove_point(new_result);
    free(result);
    free(new_result);
}
END_TEST

START_TEST(test_lines) {
    get_polygons_from_file("notExistFile");
    line_vector* result = get_polygons_from_file("test.obj");
    ck_assert_int_eq(result -> size, 6);
    remove_line(result);
    free(result);
}
END_TEST

Suite *suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Parser check");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_points);
  tcase_add_test(tc_core, test_lines);
  suite_add_tcase(s, tc_core);

  return s;
}

int parser_test_func() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}

int main() {
  int no_failed = 0;

  no_failed |= parser_test_func();

  // return 0;
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}