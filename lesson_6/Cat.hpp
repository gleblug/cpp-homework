#include <string>

class Cat {
private:
  std::string color;
  std::string name;
  int pos;
  bool hungry;
public:
  static std::string sound;
  int position() {
    return pos;
  }

  int go_forward();

  int go_backward();
};
