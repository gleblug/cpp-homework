# Пятый семинар
## Структуры

```cpp
struct Person {
  Person (std::string str1, std::string str2, unsigned short num1, int num2 = 0):
    name(str1), surname(str2), age(num1), salary(num2) { // Инициализация (в отличие от объявления + присваивания)
    // name = str1;
    // surname = str2;
    // age = num1;
    // salary = num2;
  }                                     // (4) КОНСТРУКТОР

  std::string     name;    //= "Bob";      // <--- данные-члены (публичные поля)
  std::string     surname; //= "Jobs";     // (2) Значения по умолчанию
  unsigned short  age;
  int             salary;
};

int main(int argc, char const *argv[]) {
  // Создание экземпляра структуры (конструктор по умолчанию, то есть свой не написан (!) ):
  Person p;

  Person* ptr1 = &p;

  Person* ptr2 = new Person[10]; // Динамический массив
  auto ptr3 = new Person;

// ИНИЦИАЛИЗАЦИЯ / ОПРЕДЕЛЕНИЕ / ПРИСВАИВАНИЕ
  // (1) Присваивание значений полям
  p.name = "Umar";
  p.age = 21;

  // (2) Значения по умолчанию

  // (3) Агрегатная инициализация | Универсальная инициализация
  Person person1 = {"Ivan", "Ivanov", 30, 300};
  Person person2{"Ivan", "Ivanov", 30, 300};

  // (4) Конструкторы
}
```

### Этапы работы конструктора

0. Есть ещё одна операция (spoiler!)
1. Создаётся (выделяется память) и инициализируются поля (в том порядке, в котором они объявлены, т.е. через список инициализации)
2. Выполняется тело конструктора

### Про выравнивание

```cpp
struct A {
  short a;
  double b;
  short c;
};

struct B {
  short a;
  short c;
  double b;
};

int main(int argc, char const *argv[]) {
  A n;
  B m;

  std::cout << sizeof(n) << " > " << sizeof(m) << '\n'; // OUT: 24 > 16
}
```

## Деструктор

```cpp
struct Person {
  Person (std::string str1, std::string str2, unsigned short num1, int num2 = 0):
    name(str1), surname(str2), age(num1), salary(num2) {
    std::cout << "Constructor launched here!" << '\n';
  }

  Person (): name("Unnamed"), surname("Unnamed"), age(0), salary(0) {
    std::cout << "Default constructor." << '\n';
  }

  ~Person() {                                   // Деструктор здесь
    std::cout << "Desctructor here!" << '\n';
  }

  std::string     name;
  std::string     surname;
  unsigned short  age;
  int             salary;
};
```

### Этапы работы деструктора

0. spoiler
1. Выполняется тело деструктора
2. Уничтожение полей (если реализован свой, то через него)

## Идиома RAII

Ресурса захват _инициализацией_ именуют, о, юный падаван.

- Захват в конструкторе
- Высвобождение в деструкторе

**Где это применимо:**

- Выделенная память
- Открытый файл
- База данных
- Соединение

## Битовые поля

```cpp
struct bitset {
  unsigned short int first: 2;  // Запрашиваем место побитово (минимум любой объект может занимать 1 байт, в тч и class/struct)
  unsigned short int second: 2;
  unsigned short int : 4;       // Можно делать безымянные поля)
};
```

## Прикольные штуки

Макрос `__func__` возвращает имя функции, в которой он использовался.
Почитать про юнион
