#include <type_traits>

using number = const long long;

template <std::size_t n>
struct Calculate_Fibonacci_Number
{
    static number value =
        Calculate_Fibonacci_Number<n - 1>::value +
        Calculate_Fibonacci_Number<n - 2>::value;
};

template <>
struct Calculate_Fibonacci_Number<0>
{
    static number value = 0; 
};

template <>
struct Calculate_Fibonacci_Number<1>
{
    static number value = 1;
};

template <int n>
number Fibonacci_Number = Calculate_Fibonacci_Number<n>::value;

int main(int argc, char const *argv[])
{
    static_assert(Fibonacci_Number<0> == 0);

    static_assert(Fibonacci_Number<7> == 13);

    static_assert(Fibonacci_Number<83> == 99194853094755497ll);

    return 0;
}
