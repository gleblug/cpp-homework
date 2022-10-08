#include <string>
#include "Cat.hpp"

int Cat::go_forward() {
  return ++(this->pos);
}

int Cat::go_backward() {
  return --(this->pos);
}

std::string Cat::sound("Meow");
