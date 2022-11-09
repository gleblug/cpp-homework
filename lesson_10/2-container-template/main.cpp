#include "Container.hpp"
#include <iostream>


int main(int argc, char const *argv[])
{
    Container<int> array = {1, 2, 3, 4, 5};

    std::cout << array << std::endl;

    return 0;
}
