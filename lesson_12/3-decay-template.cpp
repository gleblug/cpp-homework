#include <iostream>
#include <cassert>

template <typename T>
struct decay
{
    using type = T;
};

template <typename T, typename... Types>
struct decay<T(Types...)>
{
    using type = T;
};

template <typename T, typename std::size_t N>
struct decay<T[N]>
{
    using type = T;
};

template <typename T>
struct decay<T[0]>
{
    using type = T;
};

template <typename T>
struct decay<T &>
{
    using type = T;
};

template <typename T>
struct decay<T &&>
{
    using type = T;
};

template <typename T>
using decay_t = typename decay<T>::type;


double func(int, int)
{ return 1.3; }

int main(int argc, char const *argv[])
{
    double arr[5];
    double empty_arr[0];
    double val = 1.3;

    bool trigger;
    using type = double;

    // function test
    trigger = std::is_same_v<decay_t<decltype(func)>, type>;
    assert(trigger);

    // array test
    trigger = std::is_same_v<decay_t<decltype(arr)>, type>;
    assert(trigger);

    // empty array test
    trigger = std::is_same_v<decay_t<decltype(empty_arr)>, type>;
    assert(trigger);

    // lvalue test
    trigger = std::is_same_v<decay_t<decltype(val)>, type>;
    assert(trigger);

    // rvalue test
    trigger = std::is_same_v<decay_t<decltype(std::move(val))>, type>;
    assert(trigger);

    // type test
    trigger = std::is_same_v<decay_t<double>, type>;
    assert(trigger);

    std::cout << "SUCCESS" << std::endl;

    return 0;
}
