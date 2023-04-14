## Хранение и использование не статичных функций-членов
```cpp
Test test; // struct Test {void print(); static void static_print()};
auto static_func = Test::static_print; // всё ок, вызывается без объекта

// первый подход

auto member_func_ptr = &Test::print; // нужен объект

(test.*member_func_ptr)(); // либо ->* для указателей

// второй подход

auto member_function = std::mem_fn(&Test::print);
member_function(test); // делает тоже самое, но более приятый синтаксис
```

## Параллельное программирование
POSIX, WINAPI, Boost

- Мнимый параллелизм
	+ Планировщик (как часть системы)
	+ Коннективное (без планировщика, программы сами отдают время процессора)
- Истинный параллелизм (аппаратный)



