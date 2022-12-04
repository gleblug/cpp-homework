#include <array>
#include <iostream>

template <std::size_t n>
class Prime
{
public:
    using value_t = long long;

    constexpr Prime() noexcept
    {
        value_t number = 2;

        std::array<value_t, n> prime_numbers;
        prime_numbers[0] = number;

        std::size_t size = 0;
        while (size < n)
        {
            bool is_prime = true;

            for (std::size_t i = 0; i < size; i++)
            {
                if (number % prime_numbers[i] == 0)
                {
                    is_prime = false;
                    break;   
                }
            }

            if (is_prime)
            {
                prime_numbers[size] = number;
                ++size;
            }
            
            ++number;
        }

        m_number = prime_numbers[n - 1];
    }

    constexpr auto number() const noexcept
    {
        return m_number;
    }

private:
    value_t m_number;
};


int main(int argc, char const *argv[])
{
    std::cout
        << std::boolalpha
        << "Test 1: " << (Prime<1>().number() == 2) << std::endl
        << "Test 2: " << (Prime<7>().number() == 17) << std::endl
        << "Test 3: " << (Prime<27>().number() == 103) << std::endl
        << "Test 4: " << (Prime<1000>().number() == 7919) << std::endl;

    return 0;
}
