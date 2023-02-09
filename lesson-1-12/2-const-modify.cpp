#include <iostream>
#include <cassert>
#include <type_traits>

template <typename T>
struct add_const
{
    using type = const T;
};

template <typename T>
struct remove_const
{
    using type = T;
};

template <typename T>
struct remove_const<const T>
{
    using type = T;
};


template <typename T>
using add_const_t = typename add_const<T>::type;

template <typename T>
using remove_const_t = typename remove_const<T>::type;

int main(int argc, char const *argv[])
{
    bool trigger;
    using type = int;

    trigger = std::is_same_v<const type, add_const_t<type>>;
    assert(trigger);

    trigger = std::is_same_v<const type, add_const_t<const type>>;
    assert(trigger);

    trigger = std::is_same_v<type, remove_const_t<const type>>;
    assert(trigger);

    trigger = std::is_same_v<type, remove_const_t<type>>;
    assert(trigger);

    std::cout << "SUCCESS" << std::endl;

    return 0;
}

