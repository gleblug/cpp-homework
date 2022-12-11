#include <iostream>
#include <iomanip>

inline constexpr double e_v = 2.718281828459045235360287471352;


template <std::size_t n>
constexpr double Calculate_Exponent()
{
    double value = 1;
    long long factorial = 1;

    for (size_t i = 1; i <= n; i++)
        value += 1.0f / (factorial *= i);
    
    return value;
}


int main(int argc, char const *argv[])
{
    constexpr std::size_t accuracy = 18;
    constexpr double epsilon = 1e-5;

    constexpr double e = Calculate_Exponent<accuracy>();
    
    static_assert(std::abs(e_v - e) < epsilon);

    return 0;
}