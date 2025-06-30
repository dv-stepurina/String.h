CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -Isrc

# Директории
SRC_DIR = src
STRING_DIR = $(SRC_DIR)/string_func
SPRINTF_DIR = $(STRING_DIR)/sprintf
TESTS_DIR = $(SRC_DIR)/tests
OBJ_DIR = obj

# Исходные файлы
STRING_FILES = $(STRING_DIR)/s21_string_func.c $(STRING_DIR)/s21_strerror.c
SPRINTF_FILES = $(SPRINTF_DIR)/s21_sprintf.c
SRC_FILES = $(STRING_FILES) $(SPRINTF_FILES)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Тестовые файлы
TEST_FILES = $(wildcard $(TESTS_DIR)/*.c)
TEST_OBJ_FILES = $(patsubst $(TESTS_DIR)/%.c,$(OBJ_DIR)/tests/%.o,$(TEST_FILES))

EXECUTABLE = s21_test_string
LIBRARY = s21_string.a

OS = $(shell uname)
ifeq ($(OS), Darwin)
	LDFLAGS = -lcheck -lpthread -lm
else
	LDFLAGS = -lcheck -lsubunit -lrt -lpthread -lm
endif

.PHONY: all clean test gcov_report style set_style cppcheck leaks

all: $(LIBRARY)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/string_func/sprintf
	mkdir -p $(OBJ_DIR)/tests

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBRARY): $(OBJ_FILES)
	ar rc $@ $^
	ranlib $@

clean:
	rm -rf $(OBJ_DIR) $(LIBRARY) $(EXECUTABLE) *.gcda *.gcno *.gcov coverage.info report

test: $(LIBRARY) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) $(TEST_OBJ_FILES) $(LIBRARY) $(LDFLAGS) -o $(EXECUTABLE)
	./$(EXECUTABLE)

gcov_report: CFLAGS += --coverage
gcov_report: clean $(LIBRARY)
	$(CC) $(CFLAGS) $(SRC_FILES) $(TEST_FILES) $(LDFLAGS) -o $(EXECUTABLE)
	./$(EXECUTABLE) || true
	lcov -t "Report" -o coverage.info -c -d .
	genhtml coverage.info -o report
	open report/index.html

style:
	clang-format -n -style=Google $(STRING_DIR)/*.c $(SPRINTF_DIR)/*.c $(TESTS_DIR)/*.c \
	$(STRING_DIR)/*.h $(SPRINTF_DIR)/*.h $(TESTS_DIR)/*.h

set_style:
	clang-format -i -style=Google $(STRING_DIR)/*.c $(SPRINTF_DIR)/*.c $(TESTS_DIR)/*.c \
	$(STRING_DIR)/*.h $(SPRINTF_DIR)/*.h $(TESTS_DIR)/*.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem \
	$(STRING_DIR)/*.c $(SPRINTF_DIR)/*.c $(STRING_DIR)/*.h $(SPRINTF_DIR)/*.h

leaks: test
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE)