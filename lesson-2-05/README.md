# Обработка текста

## Локали
```cpp
#include <ios>
#include <iostream>
#include <iomanip>
#include <locale>

int main(int argc, char const *argv[])
{
	std::cout << "⚠️  Важное сообщение! Ты молодец! 😀\n" << std::endl;

	// вывод деняг
	auto loc = std::locale("ru_RU.utf8");
	const uint value = 12323;
	std::cout.imbue(loc);
	std::cout << std::showbase << std::put_money(value, false) << std::endl;

	// приём деняг
	std::get_money(...);

	return 0;
}
```