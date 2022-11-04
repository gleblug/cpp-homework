#pragma once
#include <stdexcept>

namespace math
{
    class division_by_zero : public std::logic_error
    {
    public:
        division_by_zero() : logic_error("Division by zero!") {}
    };

    class invalid_value : public std::invalid_argument
    {
    public:
        invalid_value(char value) : invalid_argument("Invalid value: " + value) {}
        invalid_value(std::string value) : invalid_argument("Invalid value: " + value) {}
    };
} // namespace math
