# Третий семинар

## Низкий уровень абстракции ("голый" C++)
### Указатели

`T *ptr` или лучше `int* ptr`, где T -- тип: указатель на T

```cpp
char c = 'a';
char* ptr;

ptr = &c; // & -- оператор взятия адреса

*ptr = `b`;
```

```cpp
ptr = nullptr; // занулить указатель (для безопасности), это нужно регулярно проверять
```

**Управление памятью**

`malloc(size_t n) -> void*`
возвращает указатель на `void` (не разыменовывается), далее можно преобразовать с помощью `static_cast`.

Для освобождения участка памяти `free(ptr)`, чтобы предотвратить утечки.

Примеры:
```cpp
#include <iostream>

int main() {
  const short AMOUNT_INT = 5;

  int* ptr = static_cast<int*>(malloc(sizeof(int) * AMOUNT_INT));

  for (int* i = ptr; i < ptr + AMOUNT_INT; i++) {
    *i = 1;
  };

  for (int* i = ptr; i < ptr + AMOUNT_INT; i++) {
    std::cout << *i << '\n';
  };

  free(ptr);
}
```

#### Расстояние между указателями

`std::distance(ptr1, ptr2)` -- расстояние между адресами (в кол-ве ячеек типа)

#### Константный указатель

`int* const p = &v` Накладывает ограничения на возможность изменение адреса, *но не данных по адресу*.

`const int* p = &b` наборот, накладывает ограничения на возможность *изменения данных по адресу*.

### Массивы

#### Статические массивы

`T a[size_t SIZE]`, SIZE - константа на момент компиляции!

`std::size(a)` -- размер массива (количество эл-тов)

При объявлении массива из тривиальных типов он заполняется мусором, иначе (другие типы) вызывается конструктор по умолчанию.

#### Инициализация массива

`int v1[6] = {1, 2, 3, 4, 5}` остальное заполнится нулями (агрегатная инициализация). Еще существует инициализация списком инициализации (пока *unknown*)

`int v1[6] = {}` будут только нули

`int v2[]{1, 2, 3, 4}` -- универсальная инициализация.

```cpp
#include <iostream>

int main() {
  int a;
  int b{}; //uniform init
  int c = {}; //aggregate init

  /*
  индексация как в python
  */
}
```

указатели:
```cpp
int main() {
  int v[]{1, 2, 3, 4, 5};
  int* ptr = &v[0];

  std::cout << *ptr << '\n' << *++ptr;
}
```

#### C-строка

`"abcd" <=> const char[]={'a', 'b', 'c', 'd', '\0'}`

```cpp
#include <iostream>

int main() {
  char my_string[] = {'a', 'b', 'c', 'd'};

  std::cout << std::size(my_string) << '\n';  // out: 4 (C-string)

  std::cout << std::size("abcd") << '\n';     // out: 5, because every string
                                              // include '\0' at the end
}
```

#### Динамический массив

Создаётся с помощью указателей и `malloc`

### Оператор `new` и `delete`

Похоже на `malloc`, но вызывает *constructor* (создаёт объект и выделяет под него память, а не просто выделяет память). Аналогично с `delete` (в отличие от `free` вызывает *destructor*)

```cpp
int main() {
  size_t n;
  std::cin >> n;

  int* ptr = new int[10];

  *ptr = 1;
  *++ptr = 2;

  std::cout << *ptr << '\n';

  delete[](ptr);
  // delete (ptr) для не массивов
}
```

### Ссылки (`rvalue` и `lvalue`)



## Высокий уровень абстракции (STD)
### Smart pointers

### Контейнеры (std::vector)


## Функции и ссылки

```cpp
#include <iostream>

void f (int& a) {
  a++;
  std::cout << "a(func)=" << a << '\n'; // out: 3
}

int main() {
  int a = 2;
  int& link = a; // создание ссылки (теперь link тождественно равен a)

  f(a);

  std::cout << "a=" << a << '\n'; // out: 3
}
```
