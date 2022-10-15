#include <iostream>

class Array {
public:
  Array (size_t length): length(length), ptr(nullptr) {
    ptr = new int[length];
  }
  Array(): length(0), ptr(nullptr) {  }

  size_t get_length() const{
    return length;
  }

  int& operator[] (size_t pos) {
    return ptr[pos];
  }

  const int& operator[] (size_t pos) const{
    return ptr[pos];
  }

  ~Array () {
    delete[] ptr;
  };

private:
  size_t length;
  int* ptr;
};

int main(int argc, char const *argv[]) {

  return 0;
}
