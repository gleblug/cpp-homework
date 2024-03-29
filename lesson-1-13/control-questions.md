# Контрольные вопросы к 13 заданию
### Что означает полнота по Тьюрингу в теории вычислимости?
Это такая характеристика исполнителя (множества вычисляющих элементов), означающая возможность реализовать на нём любую вычислимую функцию. Это значит, что для каждой вычислимой функции существует вычисляющий её компонент или определённая программа для исполнителя. При это все функции, вычисляемые исполнителем, являются вычислимыми.

### Как можно использовать вычисления на этапе компиляции?
1. С помощью рекурсивного инстанцирования шаблонов,
2. возможностей `constexpr`,
3. compile-time if 
4. и идиомы SFINAE.

### Какие языковые механики работают на этапе компиляции?
1. Выражения `constexpr`;
2. Инстанцирование шаблонов;
3. Static-операторы и функции (`static_cast`, `static_assert`).

### Какие ограничения имеет метапрограммирование шаблонов?
1. Максимальная глубина рекурсии компилятора;
2. Невозможность использования run-time возможностей языка (в гибридном можно);

### Как устроено гибридное метарограммирование шаблонов?
Гибридное метапрограммирование содержит как compile-time, так и run-time действия. В таком варианте метапрограммирования мы должны использовать спецификатор `constexpr`, который объявляет, что можно вычислить значение функции или переменной во время компиляции. Затем такие переменные и функции могут использоваться там, где разрешены только `constexpr`-выражения (постоянные времени компиляции).