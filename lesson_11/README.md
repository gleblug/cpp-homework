#  Вариативные шаблоны

*Зачем?*

### Динамический гетерогенный массив
```
                Фиксированный       Динамический размер
Гомогенные      T[], std::array     new[], std::vector
Гетерогенные    std::pair                  ???
```

**Ответ:** 
- `std::tuple<int,int,double,...>(...)` -- compile-time const size and types
- runtime: -- std::vector + std::any (any.cast<T> -> T value)

### Функция, которая оборачивает другую функцию
Как декоратор

### Функция, принимающая произвольное количество элементов

## Свёртки

args -- пакет параметро функции

an -- n-й элемент пакета

\# -- бинарный оператор

`(args...#) == a1 # (a2 # (... # (an)...))` -- правосторонняя унарная свёртка
`(#...args) == ...` -- левосторонняя у.с.

```cpp
#include <iostream>


// РЕКУРСИВНЫЙ ВАРИАНТ
// template <typename T>
// void print(T a)
// {
//     std::cout << a << std::endl;
// }

// пакет параметров шаблона -- Types
// пакет параметров функции -- args
template <typename... Types>
void print(Types... args)
{
    // количество аргументов -- sizeof...
    // std::cout << sizeof...(Types) << " " << sizeof...(args) << std::endl;
    // РЕКУРСИВНЫЙ ВАРИАНТ
    // std::cout << a << ' ';
    // print(args...);

    // (std::cout << ... << args) << std::endl;
    (... , (std::cout << args << ' ')) << std::endl;

    // правосторонняя унарная свёртка
    // int a = (args + ...);
}



// две пачки в одну функцию -- ?
// эквивалентность f(args...) и f((args , ...))

int main(int argc, char const *argv[])
{
    print(1, 2, 0.1, "Hello!");

    return 0;
}
```

## Статический и динамический полиморфизм

## Паттерн проектирования CRTP

замена динамического полиморфизма

```cpp
template <typename T>
class Base{};

class Derived : public Base<Derived> {};
```
+см. паттерн проектирования mix in