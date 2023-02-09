#include <iostream>
#include <cassert>

// variative template with fold expression
template <typename... Ts>
std::size_t memory_counter_fe(Ts... args)
{
    return (... + sizeof(args));
}

// recursive variative template
template <typename T>
std::size_t memory_counter_r(T a)
{
    return sizeof(a);
}

template <typename T, typename... Ts>
std::size_t memory_counter_r(T a, Ts... args)
{
    return sizeof(a) + memory_counter_r(args...);
}


int main(int argc, char const *argv[])
{
    int a;
    double b;
    char c;

    std::size_t count_of_bytes = sizeof(a) + sizeof(b) + sizeof(c);
    
    // tests
    assert(memory_counter_fe(a, b, c) == count_of_bytes);
    assert(memory_counter_r(a, b, c) == count_of_bytes);

    // tests passed successfully
    std::cout << "SUCCESS" << std::endl;

    return 0;
}
