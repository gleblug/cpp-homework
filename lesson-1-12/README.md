# Дополнения к предыдущим семинарам. Часть 1.
### Универсальные ссылки
(пробрасывающие ссылки)

```cpp
template <typename T>
void f(T&&){}
    // универсальная ссылка

template <typename T>
void f(std::vector<T&&>){}
    // НЕ универсальная ссылка
```

### Идеальная передача

Задача передачи агрумента через обёртку функции таким образом, чтобы аргумент передавался как будто сразу в функцию.

Правила свёртки ссылок: lvalue всегда в приоритете, то есть две rvalue дадут rvalue, в другом случае случае -- lvalue

```cpp
#include <iostream>
#include <type_traits>

template <typename T> // убирает ссылки с типа, в результате param всегда lvalue
T&& forward(std::remove_reference_t<T> &param)
{                     // используем правило свёртки
    return static_cast<T&&>(param);
}

void func(int &a)
{
    std::cout << "int &" << std::endl;
}

void func(int const &a)
{
    std::cout << "int const &" << std::endl;
}

void func(int &&a)
{
    std::cout << "int &&" << std::endl;
}

template <typename T>
void wrapper(T &&a)
{
    func(forward<T>(a));
}

int main(int argc, char const *argv[])
{
    int a = 5;
    int const b = 5;

    wrapper(a);
    wrapper(b);
    wrapper(5);

    return 0;
}
```