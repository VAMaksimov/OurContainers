OS = $(shell uname)
CC = g++

# Flags
MAIN_FLAGS = -std=c++17
DEBUG_FLAGS = -Wall -Wextra -Werror
VALG_FLAGS = -g
POSIX_FLAG = -D_POSIX_C_SOURCE=201706L
COVLAGS =-fprofile-arcs -ftest-coverage
# The -L flag in the g++ compiler is used to specify a directory where
# the linker should look for libraries during the linking phase of compilation.
# When you use -L/usr/lib/, you are instructing the linker to include /usr/lib/ as one of the directories to search for libraries
CHLIB = -L/usr/lib/ -lgtest -lgtest_main -pthread #-Wl,--no-warn-search-mismatch
MATHLIB = -lm 
LIBFLAGS= $(CHLIB) #$(MATHLIB)
ifeq ($(OS), Linux)
	ifeq ($(shell cat /etc/os-release | grep -c 'debian'),1)
		CHLIB += -lsubunit
	endif
endif

# Checkers
VALG = valgrind --tool=memcheck  --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$(VALG_FILE) ./
CPPCHECK = cppcheck --enable=all --suppress=missingIncludeSystem  --force --check-level=exhaustive --checkers-report=$(CPPCHECK_FILE) 
CLANG = clang-format --style=Google

# directories 
BUILD_DIR = build
SRC_DIR=src
TEST_DIR=tests
OBJ_DIR = $(BUILD_DIR)/service_files
COV_DIR = $(BUILD_DIR)/coverage
VALG_FILE = $(BUILD_DIR)/RESULT_VALGRIND.txt
CPPCHECK_FILE = $(BUILD_DIR)/RESULT_CPPCHECK.txt

# main files 
SRC_FILES = $(shell find $(SRC_DIR)/ -type  f -name '*.cpp')
HEAD_FILES = $(shell find $(SRC_DIR)/ -type f -name '*.hpp')
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.cpp=.o)))

# test files
TEST_SRC_FILES = $(shell find $(TEST_DIR)/ -type f -name '*.cpp')
TEST_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRC_FILES:.cpp=.o)))
TEST_EXEC = $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SRC_FILES:.cpp=)))
TEST_COV_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRC_FILES:.cpp=.cov.o)))
TEST_COV_EXEC = $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SRC_FILES:.cpp=_cov)))

# lib files		(unique for a project)
PROJECT_NAME=s21_matrix_oop
MAIN_HEADER=$(SRC_DIR)/$(PROJECT_NAME:=.hpp)
LIB_NAME=$(PROJECT_NAME:=.a)
LIB_COV_NAME=$(PROJECT_NAME:=.cov.a)
LIB_LOC=$(BUILD_DIR)/$(LIB_NAME)

# target specific variables
$(LIB_NAME): MAIN_FLAGS:= $(MAIN_FLAGS) $(DEBUG_FLAGS) $(POSIX_FLAG) #$(VALG_FLAGS)
$(TEST_EXEC): MAIN_FLAGS:= $(MAIN_FLAGS) $(DEBUG_FLAGS) $(POSIX_FLAG) #$(VALG_FLAGS)
$(LIB_COV_NAME): MAIN_FLAGS:=  $(MAIN_FLAGS) $(DEBUG_FLAGS) $(POSIX_FLAG) $(COVLAGS)
$(TEST_COV_EXEC): MAIN_FLAGS:= $(MAIN_FLAGS) $(DEBUG_FLAGS) $(POSIX_FLAG) $(COVLAGS)


# targets
all: $(LIB_NAME)

# library
$(LIB_NAME): clear_o $(OBJ_DIR) $(OBJ_FILES)
	ar rcs $@ $(OBJ_FILES)
	@mv $(LIB_NAME) $(LIB_LOC)
	@cp $(MAIN_HEADER) $(BUILD_DIR)

$(LIB_COV_NAME): clear_o $(OBJ_DIR) $(OBJ_FILES)
	ar rcs $@ $(OBJ_FILES)            

# tests
$(TEST_EXEC): clear_o $(LIB_NAME) $(TEST_OBJ_FILES)
	$(CC) $(MAIN_FLAGS) $(TEST_OBJ_FILES) -o $@ $(LIB_LOC) $(LIBFLAGS)
	make -s clear_o

test: $(TEST_EXEC)
	@./$(TEST_EXEC)


$(TEST_COV_EXEC): clear_o $(LIB_COV_NAME) $(TEST_OBJ_FILES)
	$(CC) $(MAIN_FLAGS) $(TEST_OBJ_FILES) -o $@ $(LIB_COV_NAME) $(LIBFLAGS)
	rm -fr $(LIB_COV_NAME)

test_cov: $(TEST_COV_EXEC)
	@./$(TEST_COV_EXEC)


# object files
$(OBJ_DIR)/%.o: %.cpp
	@$(CC) $(MAIN_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: */%.cpp
	@$(CC) $(MAIN_FLAGS) -c $< -o $@


# coverage & report
coverage: test_cov
	gcov -b --object-directory=$(OBJ_DIR) $(SRC_FILES)  

gcov_report: $(COV_DIR) coverage
	gcovr  --object-directory $(OBJ_DIR)  -r . --html --html-details --output=$(COV_DIR)/    
	@make -s clear_gc
	@make -s clear_o


# deployment
dep_lib: $(LIB_NAME)
	@cp $(MAIN_HEADER) $(BUILD_DIR)/$(notdir $(MAIN_HEADER))


#checkers 
format_all:
	$(CLANG) -i $(HEAD_FILES) $(SRC_FILES) $(TEST_SRC_FILES) $(MAIN_HEADER)

format_check:
	@$(CLANG) -n $(HEAD_FILES) $(SRC_FILES) $(TEST_SRC_FILES) $(MAIN_HEADER)
	$(CLANG) -n $(shell find . -type f -name '*.cpp' -o -name '*.hpp')

valgrind: $(TEST_EXEC)
	$(VALG) $(TEST_EXEC)

cppcheck:
	$(CPPCHECK) $(shell find $(TEST_DIR) $(SRC_DIR) -type f \( -name '*.cpp' -o -name '*.hpp' \))


# service
$(OBJ_DIR) $(BUILD_DIR) $(COV_DIR):
	@mkdir -p $@

clear_o: 
	@rm -fr $(OBJ_DIR)

clear_gc:
	@rm -fr $(OBJ_DIR)/*.gc*	
	@rm -fr *.gc*

clear_cov:
	@rm -fr $(COV_DIR)

clean: clear_cov clear_gc clear_o
	rm -fr $(BUILD_DIR) $(LIB_NAME) $(LIB_COV_NAME) $(VALG_FILE)  $(CPPCHECK_FILE)  

clear: clean

rebuild_test: clean test

rebuild_test_cov: clean test_cov

rebuild_report: clean gcov_report


.PHONY: test $(LIB_NAME) gcov_report clean all 