#include <iostream>
#include <iomanip>

inline constexpr double e_v = 2.718281828459045235360287471352;

template <std::size_t n>
struct Calculate_Factorial
{
    static constexpr long long value = Calculate_Factorial<n - 1>::value * n;
};

template <>
struct Calculate_Factorial<0>
{
    static constexpr long long value = 1;
};

template <std::size_t n>
constexpr long long Factorial = Calculate_Factorial<n>::value;


template <std::size_t n>
struct Calculate_Exponent
{
    static constexpr double value = Calculate_Exponent<n - 1>::value + 1.0 / Factorial<n>;
};

template <>
struct Calculate_Exponent<0>
{
    static constexpr double value = 1;
};

template <std::size_t n>
constexpr double Exponent = Calculate_Exponent<n>::value;


int main(int argc, char const *argv[])
{
    constexpr std::size_t accuracy = 20;
    constexpr double epsilon = 1e-15;

    constexpr double e = Exponent<accuracy>;
    
    static_assert(std::abs(e_v - e) < epsilon);

    return 0;
}