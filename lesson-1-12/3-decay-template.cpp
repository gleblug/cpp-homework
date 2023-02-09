#include <iostream>
#include <cassert>
#include <functional>


// if then else impl
template <bool B, typename T, typename F>
struct if_then_else
{
    using type = T;
};

template <typename T, typename F>
struct if_then_else<false, T, F>
{
    using type = F;
};

template <bool B, typename T, typename F>
using if_then_else_t = typename if_then_else<B, T, F>::type;


// decay impl
template <typename T>
struct decay
{
    using type = 
        if_then_else_t<std::is_lvalue_reference_v<T>, std::remove_reference_t<T>,
        if_then_else_t<std::is_rvalue_reference_v<T>, std::remove_reference_t<T>,
        if_then_else_t<std::is_array_v<T>, std::remove_all_extents_t<T>,
        T
    >>>;
};

template <typename T, typename... Types>
struct decay<T(Types...)>
{
    using type = T;
};

// template <typename T>
// struct decay<T[]>
// {
//     using type = T;
// };

// template <typename T>
// struct decay<T[0]>
// {
//     using type = T;
// };

template <typename T>
using decay_t = typename decay<T>::type;


// tests
using type = double;

type func(int, int)
{ return 1.3; }

int main(int argc, char const *argv[])
{
    type arr[5];
    type zero_arr[0] = {};
    type null_arr[] = {};
    type val = 1.3;

    bool trigger;

    // array test
    trigger = std::is_same_v<decay_t<decltype(arr)>, type>;
    assert(trigger);

    // zero test
    trigger = std::is_same_v<decay_t<decltype(zero_arr)>, type>;
    assert(trigger);

    // null array test
    trigger = std::is_same_v<decay_t<decltype(null_arr)>, type>;
    assert(trigger);

    // function test
    trigger = std::is_same_v<decay_t<decltype(func)>, type>;
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
