#include <exception>
#include <iostream>
#include <array>
#include <vector>

int main(int argc, char const *argv[]) {
    // invalid argument
    try {
        int number = std::stoi("Hello world!");
    }
    catch (std::invalid_argument const &e) {
        std::cerr << e.what() << ": invalid argument" << '\n';
    }

    // length error
    try {
        std::vector<int> vector;
        vector.reserve(vector.max_size() + 1);
    }
    catch (std::length_error const &e) {
        std::cerr << e.what() << ": length error" << '\n';
    }

    // out of range
    try {
        std::array<int, 4> array;
        array.at(4) = 1;
    }
    catch (std::out_of_range const &e) {
        std::cerr << e.what() << ": out of range" << '\n';
    }

    // bad alloc
    try {
        std::vector<std::string> strings;
        strings.reserve(strings.max_size());
    }
    catch(std::bad_alloc const& e) {
        std::cerr << e.what() << '\n';
    }

    // bad cast
    try {
        struct Foo { virtual ~Foo() {} };
        struct Boo { virtual ~Boo() {} };

        Boo boo;

        Foo& foo = dynamic_cast<Foo&>(boo);
    }
    catch(std::bad_cast &e) {
        std::cerr << e.what() << '\n';
    }
}

