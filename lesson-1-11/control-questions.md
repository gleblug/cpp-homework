# Вариативные шаблоны
### Приведите примеры ситуаций, в которых удобно использовать вариативные шаблоны

- Для функции-обёртки -- например, emplace_back -- где мы изначально не знаем количество и тип аргументов;
- Для гетерогенного динамического контейнера;
- Для функции, принимающей произвольное число аргументов.

### Как можно по очереди обработать все аргументы из пакета параметров функции?

С помощью рекурсивного инстанцирования шаблона.

### Как вычислить количество параметров в пакете параметров вариативного шаблона?

С помощью `sizeof...(Types)`.

### Какие существуют разновидности выражений свёртки и когда они применяются? 

Свёртки разделяют на правосторонние и левосторонние, а также на унарные и бинарные. Их применение уместно, когда нам нужно обработать весь пакет параметров с помощью одного оператора или обработать их как отдельные выражения, например, вот так:
```cpp
template <typename... Types>
void print(Types... args)
{
    (... , (std::cout << args << ' ')) << std::endl;
}
```
Здесь мы применяем оператор `,` для выражения `std::cout << args << ' '` для каждого аргумента из пакета параметров. В результате функция `print` выводит, чередуя пробелами, все переданные аргументы в стандартный поток вывода по очереди.

### В чём заключается разница между динамическим и статическим полиморфизмом?

*Динамический полиморфизм* подразумевает использование наследования классов в совокупности с механизмом виртуальных функций, который обеспечивает возможность вызывать правильные перегруженные методы объекта, даже если указатель на него будет иметь тип родительского класса.

*Статический полиморфизм* позволяет реализовать в точности ту же идею, но может быть релизован с помощью вариативных шаблонов таким образом, что мы не будем прибегать к использованию виртуальных функций, что делает код более быстрым.