#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_H_

// 1) Related header
// 2) C system headers
// 3) C++ standard library headers
// 4) other libraries' headers
// 5) project's headers.
#include "components/s21_stack_queue.h"
#include "components/s21_set.h"
#include "components/s21_sorted_container.h"
#include "components/s21_list.h"
/// @brief вот то что ниже вынесте в отдельный файл  и в папку components , а
/// здесь чисто инклюды оставить

// namespace s21 {
// template <typename T>
// class Container {
//  public:
//   using value_type_ = T;
//   using reference_ = T &;
//   using const_reference_ = const T &;
//   // defines the type of the container size (standard type is size_t)
//   using size_type_ = unsigned long long;

//   // Compiler provides the constructor and/or destructor automatically when
//   // `= default` is used
//   Container() = default;
//   // If a derived class is permitted to override a base class’s methods,
//   // the virtual keyword is used. By adding virtual to a method’s definition,
//   // it is declared that a derived class’s implementation should be used if
//   one
//   // is supplied.
//   // Within the implementation, the override keyword to the
//   // method’s declaration is added
//   virtual ~Container() = default;

//   // Writing = 0 after a member function inside a class declaration
//   // marks that function as pure virtual. A pure virtual function indicates
//   that
//   // the class is abstract and cannot be instantiated directly
//   virtual bool empty() const = 0;
//   virtual size_type_ size() const = 0;
// };

// }  // namespace s21

#endif  // CPP2_S21CONTAINERS_S21_CONTAINERS_H_