GCC=g++
GFLAGS=-Wall -Werror -Wextra -std=c++17 -g
GOVFLAGS=--coverage
TEST_FLAGS=-lgtest_main -lgtest
OTHER_LIB=
SANITIZE_FLAGS=-fsanitize=address,undefined

APP_TEST=test.bin
H_LIB=s21_contaners.h
H_LIB_PLUS=s21_contanersplus.h
#directory
BUILD_DIR=build

HDIR=components
TEST_DIR=tests
BIN_DIR=$(BUILD_DIR)/bin
OBJ_DIR=$(BUILD_DIR)/obj
COVERAGE_DIR=$(BUILD_DIR)/coverage

#file`s lists
SRC_H=$(wildcard $(HDIR)/*.h)
SRC_TEST=$(wildcard $(TEST_DIR)/*.cc)

#arifacts
OBJ_DIR=$(BUILD_DIR)/obj

#artifacts`s prefix
OBJS_TEST=$(addprefix $(OBJ_DIR)/, $(notdir $(SRC_TEST:.cc=.o)))

#os
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	GTESTFLAGS=$(shell pkg-config --cflags --libs gtest gtest_main)
	OPEN=xdg-open 
else ifeq ($(UNAME_S),Darwin)
	GTESTFLAGS=-lgtest -lgtest_main -lpthread
	OPEN=open
endif

IS_WSL := $(shell uname -r | grep -i microsoft)

.PHONY: test clean gcov_report style_check format

all: clean test

test: $(OBJS_TEST)
	@mkdir -p $(BIN_DIR)
	$(GCC) $(GFLAGS) $(OBJS_TEST) -lgcov -I. $(SRC_H) $(OTHER_LIB) -o $(BIN_DIR)/$(APP_TEST) $(GTESTFLAGS)
	cp $(BIN_DIR)/$(APP_TEST) .
	./$(APP_TEST)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(GCC) $(GFLAGS) $(GOVFLAGS) $(GTESTFLAGS) -I$(HDIR) -I. -c $< -o $@

gcov_report: clean test
	@mkdir -p $(COVERAGE_DIR)
	./$(BIN_DIR)/$(APP_TEST)
	lcov --capture --directory $(OBJ_DIR) --output-file $(COVERAGE_DIR)/coverage.info \
		--include "$(PWD)/components/*.h" \
		--include "$(PWD)/tests/*.cc" \
		--ignore-errors mismatch 
	genhtml -o $(COVERAGE_DIR) $(COVERAGE_DIR)/coverage.info
	@if [ -n "$(IS_WSL)" ]; then \
		explorer.exe `wslpath -w $(COVERAGE_DIR)/index.html` || true; \
	else \
		$(OPEN) $(COVERAGE_DIR)/index.html; \
	fi


sanitize: GFLAGS += $(SANITIZE_FLAGS)
sanitize: clean test

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n $(TEST_DIR)/*.cc $(HDIR)/*.h *.h
	rm .clang-format

format:
	cp ../materials/linters/.clang-format .
	clang-format -i $(TEST_DIR)/*.cc $(HDIR)/*.h *.h
	rm .clang-format

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./$(BIN_DIR)/$(APP_TEST)

clean:
	rm -rf $(BUILD_DIR) $(APP_TEST)

cppcheck:
	cppcheck --language=c++ --enable=all \
	--suppress=postfixOperator --suppress=noExplicitConstructor --suppress=missingIncludeSystem --std=c++17 \
	 -I$(HDIR) $(TEST_DIR)/*.cc -I.


clang_tidy:
	clang-tidy $(SRC_TEST) -- $(GFLAGS) -I$(HDIR) -I.