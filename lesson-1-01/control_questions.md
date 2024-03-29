## Контрольные вопросы к первому заданию:

1. Прокомментируйте основные характеристики языка C++.

  _C++ -- компилируемый, мультипарадигменный, статически типизированный язык программирования._
  - **Компилируемый** -- это значит, что перед получением исполняемого файла программы (для Windows `.exe`) код из файла `.cpp` должен пройти через компилятор (этап компиляции), в отличие от интерпретируемых языков программирования.
  - **Мультипарадигменный** -- значит, что существует несколько подходов (парадигм) к написанию кода. Например, ООП, структурное или функциональное программирование. Сейчас чаще всего применяют объектно-ориентированный подход как наиболее универсальный и удобный в использовании.
  - **Статически типизированный** -- значит, что все переменные и функции должны иметь определённый тип, который нельзя менять далее в программе. В отличие от динамической типизации (напр., в Python) это позволяет значительно увеличить производительность программы, так как для каждой переменной выделятся необходимый ей объём памяти с заданным адресом.

2. Перечислите фундаментальные типы данных и укажите их особенности.

  - `bool` логический тип, занимает в памяти 1 байт, принимает значения _true/false_.
  - `char` символьный тип (256 символов в кодировке ASCII), занимает в памяти также 1 байт. Существуют производные типы: `wchar_t`, `char16_t`, `char32_t`, которые могут вмещать большее "широкие" по объему кодировки.
  - `int` целочисленный тип (диапазон от -2'147'483'648 до 2'147'483'647), занимает в памяти 4 байта. Существуют производные типы: `short int` и `long int`, которые отличаются объёмом занимаемой памяти и, соответственно, диапазоном хранимых данных.
  - `double` и `float` типы для чисел с плавающей точкой. `double` занимет в памяти 8 байт, `float` -- 4. Применимы все те же операции, что и к `int`.
  - `void` отсутствие типа. Используюется для функции, если они ничего не возвращает.

3. Когда возникает проблема переносимости и как её предотвратить?

  Проблема переносимости возникает при переносе кода программы на другую программную-аппаратную платорму, из-за чего некоторые функции могут не работать и программа будет завершаться с ошибкой. Это происходит из-за отстутсвия поддержки необходимых функций и драйверов. Для предотвращения этой проблемы разработчики ещё при создании продукта задумываются о портировании на другие платформы, ведь зачастую это намного дешевле создания продукта с нуля. 

4. Что такое определение, объявление, инициализация и присваивание?

  - Инициализация: `int a = 5;`. Объявление и определение переменной (задаём тип, имя и значение).
  - Объявление: `int a;`. При объявлении задаётся только имя и тип переменной.
  - Определение (после объявления): `a = 5;`. Может быть только одно на всю программу.
  - Присваивание (переменная уже опеределена): `a = 5`. Изменяет значение переменной.

5. Почему выравнивание данных в памяти увеличивает производительность?

  Благодаря выравниванию данных процессор быстрее извлекает данные из памяти, так как на чтение на запись ячейки памяти потребуется по одной инструкции. Без выравнивания может случиться так, что процессору придется использовать две и более инструкции для доступа к данным, расположенным между адресами, кратными размеру машинного слова. На старых процессорах это может не только замедлить работу, процессор   может упасть с ошибкой о невалидной конструкции. Исключением является тип `char`, так как он занимает ровно одно машинное слово и всегда требует одинаковое количество инструкций для вывода.
