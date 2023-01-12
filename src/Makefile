CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TST_LIBS = -lcheck
ifeq ($(shell uname), Linux)
	TST_LIBS += -lpthread -lrt -lsubunit -lm
endif
LIB_NAME = s21_parser

SRCS=$(wildcard parser/*.c data_containers/*.c)

OBJS=$(SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIB_NAME).a: $(OBJS)
	ar rc $(LIB_NAME).a $^
	ranlib $(LIB_NAME).a
	rm -rf parser/*.o
	rm -rf data_containers/*.o

all: uninstall install gcov_report dvi dist

install: delete_temp_build recreate_build_dir
	@mkdir .temp_build
	@cd .temp_build/ && qmake ../3dviewer/3dviewer.pro && make && mv 3dviewer.app ../build/3dviewer.app
	rm -rf .temp_build
uninstall: 
	@rm -rf build

tests: clean $(LIB_NAME).a
	$(CC) $(FLAGS) check.c $(LIB_NAME).a $(TST_LIBS) -o tests
	./tests

add_coverage_flag:
	$(eval FLAGS += --coverage)

gcov_report: add_coverage_flag tests
	rm -rf reports/
	mkdir reports
	./tests
	rm -rf check*.gcda check*.gcno
	gcov -b -l -p -c *.gcno
	gcovr -o gcov_report.html --html --html-details
	rm -rf data_containers/*.gcda data_containers/*.gcno
	rm -rf parser/*.gcda parser/*.gcno
	mv *html reports/
	mv *css reports/
	open reports/gcov_report.html

dvi:
	@doxygen conf && mv html documentation
	@open documentation/index.html

dist:
	@rm -rf dist.tar.gz
	@tar -cvzf dist.tar.gz build/3dviewer.app

delete_temp_build:
	rm -rf .temp_build

recreate_build_dir:
	@rm -rf build
	@mkdir build

clean:
	rm -rf reports/* *.o test *.a *.gcno *.gcda *.gcov *.html *.css
	rm -rf data_containers/*.gcda data_containers/*.gcno
	rm -rf parser/*.gcda parser/*.gcno


all: clean tests
