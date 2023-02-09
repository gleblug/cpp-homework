#include <type_traits>
#include <cassert>
#include <iostream>

template <typename T>
struct is_function : std::false_type
{
};

template <typename T, typename... Types>
struct is_function<T(Types...)> : std::true_type
{
    using type = T;
};

template <typename T>
bool is_function_v = is_function<T>::value;

template <typename T>
using is_function_t = typename is_function<T>::type;

double func(int, int)
{
    return 1.2;
}

int main(int argc, char const *argv[])
{
    bool trigger;

    trigger = is_function_v<decltype(func)> == true;
    assert(trigger);

    trigger = is_function_v<decltype(1)> == false;
    assert(trigger);

    trigger = std::is_same_v<is_function_t<decltype(func)>, double>;
    assert(trigger);

    std::cout << "SUCCESS" << std::endl;

    return 0;
}
