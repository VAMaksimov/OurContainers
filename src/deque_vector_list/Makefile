CXX = g++
CXX_FLAGS = -Wall -Werror -Wextra -std=c++17
TEST_OBJECT=list_test.o 
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -fPIC
UNAME_S := $(shell uname -s)
COVERAGE = -fprofile-arcs -ftest-coverage
STATIC_LIBRARY=list.a
STATIC_LIB_FOR_REPORT=gcov_s21_matrix.a


ifeq ($(UNAME_S),Linux)
    TEST_FLAGS=-pthread $$(pkg-config --cflags --libs gtest gmock) -lgcov
	OPEN = xdg-open
endif
ifeq ($(UNAME_S),Darwin)
    TEST_FLAGS=-pthread -lgtest -lgtest_main -lgmock
	IGNORES= --ignore-errors usage,usage --ignore-errors inconsistent
	OPEN = open
endif


main: clean
	g++ list.cpp

list.a:
	$(CXX) $(CXXFLAGS) list.h -c $(SRC_FILES)
	ar rcs list.a *.o

deque.a:
	$(CXX) $(CXXFLAGS) deque.h -c $(SRC_FILES)
	ar rcs deque.a *.o

test_list: clean list_test.o list.a
	$(CXX) $(CXX_FLAGS) list_test.o  list.a $(TEST_FLAGS) -o test_list.out
	./test_list.out

test_deque: clean deque_test.o deque.a
	$(CXX) $(CXX_FLAGS) deque_test.o  deque.a $(TEST_FLAGS) -o test_deque.out
	./test_deque.out

list_test.o: clean
	g++ -Wall -Werror -Wextra -std=c++17 $(TEST_FLAGS) -c list_test.cpp

deque_test.o:
	g++ -Wall -Werror -Wextra -std=c++17 $(TEST_FLAGS) -c deque_test.cpp

clean:
	rm -f *.a
	rm -f *.o
	rm -f *.out
	rm -f *.gch