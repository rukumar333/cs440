#include <iostream>
#include <string>
#include <memory>
#include "SharedPtr.hpp"

class Base {
 public:
  // char *str_;
  int a;
  Base() {
	a = 0;
  }
};

class Derived : public Base {
 public:
  int b;
  int c;
  char *str;
  Derived() : Base() {
	b = 1;
	c = 2;
	str = new char[10];
  }
  ~Derived() {
	// if (str != nullptr) {
	  delete[] str;
	  // str = nullptr;
	// }
  }
};

void should_not_compile();

int main() {
  Base *b = new Base();
  Derived *d = new Derived();
  Derived *d_2 = new Derived();
  cs540::SharedPtr<Base> b_ptr{b};
  cs540::SharedPtr<Base> b_ptr2{d};
  cs540::SharedPtr<Derived> d_ptr2_2{d_2};
  // std::shared_ptr<Base> b_their_ptr{b};
  // std::shared_ptr<Base> b_their_ptr2{d};
  // std::shared_ptr<Derived> d_their_ptr2_2{d_2};
  // delete d;
  // delete d_2;
  return 0;
}

void should_not_compile() {
  // Base *b = new Base();
  // cs540::SharedPtr<Derived> ptr{b};
  // Base *b_their = new Base();
  // std::shared_ptr<Derived> ptr_their{b_their};
}
