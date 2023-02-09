#include <iostream>
#include <cassert>
#include <functional>
#include <utility>

template <typename Func, typename... Types>
auto wrapper(Func &func, Types &&...args) -> decltype(func(args...))
{
    return func(std::forward<Types>(args)...);
}


int main(int argc, char const *argv[])
{
    std::function<void()> foo = [](){};

    std::function<void(int &)> boo = [](int &a){ a++; };

    std::function<int(int, int)> sum = [](int a, int b){ return a + b; };

    int a = 1;

    // tests
    wrapper(foo);

    wrapper(boo, a);
    boo(a);
    assert(a == 3);

    assert(wrapper(sum, 1, 2) == sum(1, 2));

    // tests passed successfully
    std::cout << "SUCCESS" << std::endl;

    return 0;
}
