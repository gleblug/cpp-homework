# Шаблоны
### Функции
```cpp
template <class T>
T max(T a, T b) {
    return a > b ? a : b;
}

int main(int argc, char const *argv[]) {
    max(2.3, 1.2);
}
```

### Классы
```cpp
template <typename T>
class A {
    
};
```

### Приведение шаблонов
```cpp
template<typename T>
void f(param a) {  }
```
1. param -- не ссылка и не указатель T => для выведения типа снимаются все ссылки и const
2. param -- ссылка, но не универсальная ссылка => для выведения типа снимаются ссылки
3. param -- универсальная ссылка (пока что не рассматриваем) >_<

### Common type

```cpp
template<typename T1, typename T2>
auto mul(T1 a, T2 b) {
    typename std::common_type<T1, T2>::type result = a * b; // выбирает общий тип
    return result;
}
```

### Полная специализация шаблона

```cpp
template<typename T>
void print(T a) {
    std::cout << a << std::endl;
}

template<>
void print<bool>(bool a) {
    std::cout << "Bool value: " << std::boolalpha << a << std::endl;
}

template<>
void print<double>(double a) {
    std::cout << "Float value: " << std::scientific << a << std::endl;
}

int main(int argc, char const *argv[]) {
    print(1);
    print(3.2);
    print(true);
    return 0;
}
```

### Приоритеты при перегрузке

1. Нешаблонные функции
2. Полная специализация
3. *спойлер*
4. Обычный шаблон



https://cppinsights.io/ -- как компилятор видит наш код


