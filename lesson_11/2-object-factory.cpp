#include <iostream>
#include <cassert>
#include <type_traits>

template <typename T, typename... Ts>
T *factory(Ts... args)
{
    return new T(args...);
}

struct A
{
    A(int a1, int a2) {}
};

struct B {};


int main(int argc, char const *argv[])
{
    A *a = factory<A>(1, 2);
    B *b = factory<B>();

    // tests
    bool trigger1 = std::is_same_v<decltype(a), A *>;
    assert(trigger1);

    bool trigger2 = std::is_same_v<decltype(b), B *>;
    assert(trigger2);

    // tests passed succesfully
    std::cout << "SUCCESS" << std::endl;

    delete a;
    delete b;

    return 0;
}
