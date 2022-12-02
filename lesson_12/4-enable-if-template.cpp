#include <type_traits>
#include <iostream>

template <bool E, typename T>
struct enable_if
{  };

template <typename T>
struct enable_if<true, T>
{
    using type = T;
};

template <bool E, typename T>
using enable_if_t = typename enable_if<E, T>::type;


template <typename T>
void test(std::enable_if_t<std::is_floating_point_v<T>, std::string> val)
{
    std::cout << val << std::endl;
}

int main(int argc, char const *argv[])
{
    test<double>("Hello, double!");
    // test<int>("Hello, int!"); // -- error

    return 0;
}
