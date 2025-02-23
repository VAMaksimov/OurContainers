// 1) Related header
// 2) C system headers
// 3) C++ standard library headers
#include <queue>
#include <stack>
// 4) other libraries' headers
#include <gtest/gtest.h>
// 5) project's headers.
#include "s21_containers.h"

using namespace s21;

template <typename T>
void CompareStacks(Stack<T> &actual, std::stack<T> &expected) {
  EXPECT_EQ(actual.size(), expected.size());

  while (!actual.empty() && !expected.empty()) {
    EXPECT_EQ(actual.top(), expected.top());
    actual.pop();
    expected.pop();
  }

  EXPECT_EQ(actual.empty(), expected.empty());
}

template <typename T>
void CompareQueues(Queue<T> &actual, std::queue<T> &expected) {
  EXPECT_EQ(actual.size(), expected.size());

  while (!actual.empty() && !expected.empty()) {
    EXPECT_EQ(actual.front(), expected.front());
    actual.pop();
    expected.pop();
  }

  EXPECT_EQ(actual.empty(), expected.empty());
}

// Test size() and empty() methods.
TEST(StackTest, InitializationAndBasicProperties) {
  Stack<int> my_stack({1, 2, 3});

  // Note: std::stack does not support initializer_list directly,
  // so we push the elements in the same order.
  std::stack<int> st;
  st.push(1);
  st.push(2);
  st.push(3);

  CompareStacks<int>(my_stack, st);
}

TEST(QueueTest, InitializationAndBasicProperties) {
  Queue<int> my_queue({1, 2, 3});

  std::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);

  EXPECT_EQ(my_queue.back(), q.back());
  CompareQueues<int>(my_queue, q);
}

TEST(StackTest, Swap) {
  Stack<int> stack1({1, 2, 3, 4, 5});
  Stack<int> stack2({6, 7, 8});
  stack1.swap(stack2);
  EXPECT_EQ(stack2.size(), 5);
  EXPECT_EQ(stack1.size(), 3);
  EXPECT_EQ(stack2.top(), 5);
  EXPECT_EQ(stack1.top(), 8);
}

// Test that an empty ContainerAdaptor behaves like an empty std::stack.
TEST(StackTest, EmptyContainer) {
  Stack<int> my_stack;
  std::stack<int> st;

  EXPECT_EQ(my_stack.size(), st.size());
  EXPECT_EQ(my_stack.empty(), st.empty());
  EXPECT_NO_THROW(st.pop());
  EXPECT_NO_THROW(my_stack.pop());
  // st.top() causes Segmentation fault
}

TEST(QueueTest, EmptyContainer) {
  Queue<int> my_queue;
  std::queue<int> q;

  EXPECT_EQ(my_queue.size(), q.size());
  EXPECT_EQ(my_queue.empty(), q.empty());
  EXPECT_NO_THROW(q.pop());
  EXPECT_NO_THROW(my_queue.pop());
  // q.front() causes Segmentation fault
}

// Capture and test the output of PrintContainer().
TEST(StackTest, PrintContainer) {
  Stack<int> stack1({10, 20, 30});
  Stack<double> stack2(
      {1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999});
  Stack<char> stack3({'a', 'b', 'c'});
  Stack<std::string> stack4({"one", "two", "three"});

  // Redirect std::cout to capture output.
  std::ostringstream oss;
  auto old_buf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  stack1.PrintContainer();
  stack2.PrintContainer();
  stack3.PrintContainer();
  stack4.PrintContainer();

  // Restore the original std::cout buffer.
  std::cout.rdbuf(old_buf);

  std::string output = oss.str();
  std::string expected =
      "10 20 30 \n"
      "1.1 2 3 8.9 4.005 5.666 6 -5 7 8 9 999 \n"
      "a b c \n"
      "one two three \n";
  EXPECT_EQ(output, expected);
}

TEST(StackTest, ConstructorCopy) {
  Stack<int> our_stack = {1, 2, 3};
  Stack<int> our_copy(our_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_copy(std_stack);
  CompareStacks<int>(our_copy, std_copy);
}

TEST(StackTest, ConstructorMove) {
  Stack<int> our_stack = {1, 2, 3};
  Stack<int> our_move(std::move(our_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_move(std::move(std_stack));
  CompareStacks<int>(our_move, std_move);
  EXPECT_EQ(our_stack.empty(), std_stack.empty());
}

TEST(StackTest, OperatorMove) {
  Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = std::move(our_stack_int);
  std_stack_empty = std::move(std_stack_int);
  CompareStacks<int>(our_stack_empty, std_stack_empty);
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(StackTest, Push) {
  Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  CompareStacks<int>(our_stack_int, std_stack_int);
}

TEST(StackTest, Pop) {
  Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.pop();
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.pop();
  CompareStacks<int>(our_stack_int, std_stack_int);
  our_stack_int.pop();
  std_stack_int.pop();
  EXPECT_TRUE(our_stack_int.empty());
  // std_stack_int.empty() causes Segmentation fault
}

TEST(QueueTest, Pop) {
  Queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.pop();
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.pop();
  CompareQueues<int>(our_queue_int, std_queue_int);
  our_queue_int.pop();
  std_queue_int.pop();
  EXPECT_TRUE(our_queue_int.empty());
  // std_queue_int.empty() causes Segmentation fault
}