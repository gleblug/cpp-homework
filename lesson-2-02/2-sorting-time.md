### Результат эксперимента
Измерения были проведены для пяти видов контейнеров с количеством элементов 1'000'000 и усреднением времени по 10 испытаниям

| Container    	| Sort time, ms | Sort type 	|
|--------------	|---------------|---------------|
| Array        	| 68			| Standart  	|
| Vector       	| 68			| Standart  	|
| Deque        	| 82			| Standart  	|
| List         	| 311			| Member-fun 	|
| Forward list 	| 2047			| Member-fun 	|

Из таблицы видно, что быстрее всех сортируется контейнер `std::array`, а медленне всех `std::list` и `std::forward_list`, причём почти в 10 раз.