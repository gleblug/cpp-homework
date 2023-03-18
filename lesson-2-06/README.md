# Потоки
```
	ios_base(состояние потока, флаги потока)
		/
	basic_ios<CharT>(специализируется)
	/ 					\
basic_istream		basic_ostream
	/ 		  \	  /		\	
   / 	basic_iostream	 \	
  /				\		  \	
istream		iostream 	ostream
```

буфер -- basic_streambuf

Классы, использующие потоки:
stringstream, fstream, cout, cin

	// отключает синхронизацию для работы с многими потоками
	// std::ios::sync_with_stdio(false);

## Состояния потоков
std::ios_state:
1. good bit -- всё ОК
2. eos bit -- конец файла
3. fail bit -- сбой (не фатальный)
4. bad bit -- фатальный сбой

good() eof() fail() bad() rdstate() clear() setstate()

## Файлы
флаги in out app ate trunc binary
