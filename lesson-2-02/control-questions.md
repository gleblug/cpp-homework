# Контрольные вопросы
### В каких ситуациях применяются типы `std::pair` и `std::tuple`?

Когда нам нужно создать пару ключ-значение разных типов вместе, мы используем `std::pair`. Если таких значений различных типов становится больше, сухществует `std::tuple` -- кортеж, который позволяет хранить вместе сколько угодно значений любых типов. Важно помнить, что кортеж не является динамическим типом данных.

### Когда следует использовать `std::array`?

Когда нам требуется относительно безопасная замена стандартного массива `[]`, то есть в случаях, когда длина массива -- константа времени компиляции и при этом нам важна индексация элементов.

### Когда следует использовать `std::vector`?

Этот тип контейнера рекомендуется использовать по-умолчанию в большинстве случаев, так как он способен динамически изменять размер и выделять память.

### Когда следует использовать `std::deque`?

Deque является двусторонней очередью и используется в тех случаях, когда у программы есть жесткие ограничения по ресурсам. Особенностью и главным преимуществом является выполнение операции вставки с каждой стороны за *O(1)*. Индексация отсутсвует.

### Когда следует использовать `std::list`?

List является двусвязным списком и используется в случаях, аналогичных Deque, но позволяет выполнять операцию вставки и удаления за *O(1)* в любое место контейнера, а не только в начало или конец. Индексация отсутсвует. Существуют двунаправленные итераторы.

### Когда следует использовать `std::forward_list`?

Forward list (односвязный список) используется, когда есть жёсткое ограничение по памяти. Индексация отсутсвует. Существуют только однонаправленные итераторы.

### Какие адаптеры контейнеров есть в стандартной библиотеке?

- Стек (last in first out -- LIFO)
- Очередь (first in first out -- FIFO)
- Очередь с приорететом (FIFO + sorting)

### Когда следует использовать контейнер circular_buffer из Boost?

Когда нужно сохранять постоянный поток данных в ограниченном по памяти месте, например, историю.

### Почему контейнер circular_buffer не может войти в стандарт?

Потому что возможна ситуация, когда `std::begin(arraay) > std::end(array)`, то есть итератор начала указывает на элемент, который стоит после элемента с итератором конца.

### Какие типы данных для работы с многомерными массивами вы можете назвать?

- `boost::multiarray`
- `std::valarray`
- Стандартный массив `int array[s1][s2]...[sN];`
- Использование `std::vector<std::vector<...std::vector<int>>>`
