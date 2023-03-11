# Метапрограммирование. SFINAE.
### Сравнение типов
```cpp
#include <iostream>

template <typename T1, typename T2>
struct is_same
{
    static bool const value = false;
};

template <typename T>
struct is_same <T, T>
{
    static bool const value = true;
};

template <typename T1, typename T2>
bool is_same_t = is_same<T1,T2>::value;

int main(int argc, char const *argv[])
{
    std::cout << is_same_t<int, double> << std::endl;
    std::cout << is_same_t<int, int> << std::endl;
    return 0;
}
```

### Реализация remove_reference_t
```cpp
#include <iostream>

template <typename T>
struct remove_reference
{
    using type = T;
};

template <typename T>
struct remove_reference<T&>
{
    using type = T;
};

template <typename T>
struct remove_reference<T&&>
{
    using type = T;
};

template <typename T>
using remove_reference_t = remove_reference<T>::type;

int main(int argc, char const *argv[])
{
    remove_reference_t<int>;    // int
    remove_reference_t<int &>;  // int
    remove_reference_t<int &&>; // int
    return 0;
}
```

## SFINAE
```
Substitution
Failure
Is
Not
An
Error
```

Простейший пример (3 способа):
```cpp
#include <iostream>
#include <vector>
// СПОСОБ 1 через тип в шаблоне
                                        // неудача при подстановке int!
template <typename T, typename = decltype(T().size())> 
int f(T const &)
{
    return 1;
}

// СПОСОБ 2 через возвращаемое функцией значение
template <typename T>               // ОПЕРАТОР "," (A, B): вычислены A и B, возвращается только B (последний результат) 
auto f(T const &) -> decltype(T().size(), int())
{
    return 1
}

// СПОСОБ 3 через аргументы функции
template <typename T> 
int f(T const &, decltype(T().size(), int()) = 0)
{
    return 1;
}

template <typename...>
int f(...)
{
    return 2;
}

int main(int argc, char const *argv[])
{
    int a{};
    std::vector<int> v{1, 2, 3};

    std::cout << f(a) << std::endl; // out 2
    std::cout << f(v) << std::endl; // out 1
    return 0;
}
```

### Проверка класса на наследование
```cpp
#include <iostream>

struct Yes 
{};
struct No
{ Yes y[2]; };

template<typename T>
T && declval(); // позволяет нам получить объект из типа (антагонист decltype)

template <typename BBase, typename DDerived>
auto detect(BBase *) -> Yes;


template <typename ...>
auto detect(...) -> No;

template <typename Base, typename Derived>
struct is_based_of
{                                               // лучше использовать is_same<T1, T2>
                                                // declval позволяет "получить" объект в любом случае (в отличие от конструктора)
    static bool const value = sizeof( detect<Base, Derived>( declval<Derived*>() ) ) == sizeof(Yes);
};

template<typename Base, typename Derived>
bool is_based_of_v = is_based_of<Base, Derived>::value;


class A {};
class B : public A {};
class C : private B {};
class D : public B {};
class E {};


int main(int argc, char const *argv[])
{
    std::cout << is_based_of_v<A, E> << std::endl; // out 0
    std::cout << is_based_of_v<A, B> << std::endl; // out 1
    return 0;
}
```