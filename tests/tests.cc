// 1) Related header
// 2) C system headers
// 3) C++ standard library headers
#include <stack>
// 4) other libraries' headers
#include <gtest/gtest.h>
// 5) project's headers.
#include "../src/s21_containers.h"

using namespace s21;

TEST(StackTest, PrintStack) {
  Stack<double> my_stack(
      {1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999});
  my_stack.PrintContainer();
}

// Test size() and empty() methods.
TEST(ContainerAdaptorTest, InitializationAndBasicProperties) {
  Stack<int> my_stack({1, 2, 3});

  // Note: std::stack does not support initializer_list directly,
  // so we push the elements in the same order.
  std::stack<int> st;
  st.push(1);
  st.push(2);
  st.push(3);

  EXPECT_EQ(my_stack.size(), 3ULL);
  EXPECT_EQ(st.size(), 3ULL);

  EXPECT_FALSE(my_stack.empty());
  EXPECT_FALSE(st.empty());
}

// Test that an empty ContainerAdaptor behaves like an empty std::stack.
TEST(ContainerAdaptorTest, EmptyContainer) {
  Stack<int> my_stack({});
  std::stack<int> st;

  EXPECT_EQ(my_stack.size(), 0ULL);
  EXPECT_TRUE(my_stack.empty());
  EXPECT_EQ(st.size(), 0ULL);
  EXPECT_TRUE(st.empty());
}

// Capture and test the output of PrintContainer().
TEST(ContainerAdaptorTest, PrintContainerOutput) {
  Stack<int> my_stack({10, 20, 30});

  // Redirect std::cout to capture output.
  std::ostringstream oss;
  auto old_buf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  my_stack.PrintContainer();

  // Restore the original std::cout buffer.
  std::cout.rdbuf(old_buf);

  std::string output = oss.str();
  std::string expected = "10 20 30 \n";
  EXPECT_EQ(output, expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}