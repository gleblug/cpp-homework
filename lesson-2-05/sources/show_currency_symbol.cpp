#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <sstream>
#include <string>

// #include <Windows.h> 

void show_currency_symbol(const std::string & locale_name)
{
	std::cout << locale_name << " : " <<
		std::use_facet < std::moneypunct < char, false > > (
			std::locale(locale_name)).curr_symbol() << std::endl;
}

int main(int argc, char ** argv)
{
	// хотим, чтобы в выводе появился значок ₽ (символ российского рубля, буква Р с перечеркнутой ножкой)

	// SetConsoleCP      (CP_UTF8); // настраиваем консоль, чтобы она могла корректно
	// SetConsoleOutputCP(CP_UTF8); // работать с выводом символов в кодировке UTF-8

	const double value = 123.10;

	// Пробуем сначала так, видим число, а за ним три квадрата - это
	// проблема с кодировками - "разговор глухонемого со слепым": символ рубля
	// в UTF-8 кодируется тремя октетами https://unicode-table.com/ru/20BD/
	// но в конструкции std::cout << ... << std::put_money(value, false)
	// эти три октета выводятся как три отдельных символа типа char, почему -
	// см. мое предположение далее, но в любом случае они по отдельности 
	// не имеют никакого смысла и выводятся в консоли просто как квадратики
	std::cout.imbue(std::locale("ru_RU.utf8"));
	std::cout << std::showbase << std::put_money(value, false) << std::endl;

	// Попробуем вывести результат не в стандартный поток вывода, а в файл.
	// Тут все просто, создаем файловый поток вывода, файл output.txt
	// создастся автоматически, если он не существует. Если существует, 
	// то будет выполняться перезапись данных в существующем файле.
	// Ищи этот файл в директории проекта, там же, где и файл исходного кода
	// Это обычный текстовый файл, сохранен в UTF-8 и в нем есть символ рубля!
	std::ofstream fout("output.txt");
	fout.imbue(std::locale("ru_RU.utf8"));
	fout << std::showbase << std::put_money(value, false) << std::endl;

	// Попробуем сделать следующее: введем промежуточную строку для хранения
	// символов в кодировке UTF-8 и запишем в нее результат std::put_money(value, false)
	// В реализации используем строковые потоки ввода-вывода, см. прошлый семестр
	// Зачем так делаем: std::put_money возвращает _Monobj<const _Money> -
	// какой-то сложный объект, для него перегружен свой (сложный) operator<<, при этом
	// у меня сильное подозрение, что этот оператор работает с кодировками не совсем
	// корректно. Поверхностный поиск вопросов по проблеме на stackoverflow привел к 
	// https://stackoverflow.com/questions/1371012/how-do-i-print-utf-8-from-c-console-application-on-windows
	// В первом комментарии под верхним ответом написано (речь о консоли):
	// Be aware that there are many bugs with UTF-8 as codepage. Most are WONTFIX.
	// Нет поводов сомневаться в правдивости этих слов, настройка консоли Windows под
	// использование UTF-8 всегда страдала от большого количества проблем и стандартные
	// потоки ввода-вывода с этими проблемами сталкиваются, не раз такое встречал.
	// Поэтому вводим посредника-строковый поток, в который выведем результат 
	// std::put_money(value, false), а посредника уже распечатаем стандартным образом
	// Запускаем, выводим - и видим один квадратик, значит три октета
	// правильно определились как компоненты одного символа в UTF-8,
	// но, тем не менее, он почему-то не вывелся как символ рубля
	std::ostringstream sout;
	sout.imbue(std::locale("ru_RU.utf8"));
	sout << std::showbase << std::put_money(value, false) << std::endl;
	std::cout << sout.str() << std::endl; // вывели в cout строку в UTF-8

	// Попробуем вывести символы разных валют напрямую через фацет
	// Видим, что некоторые символы отображаются корректно, но
	// некоторые рисуются как квадратики. Появляется подозрение,
	// что консоль просто не умеет рисовать некоторые символы
	// (вернее не консоль, а тот шрифт, который в ней сейчас
	// активен). Попробуем поменять шрифт на Consolas (!)
	// https://myitstuff.ru/25-the-font-of-the-windows-console-cmd-exe
	// Нажимаем ОК, и видим, что символ рубля наконец появился, ура!

	auto loc_file = std::ifstream("/home/glebi/git/cpp-homework/lesson-2-05/sources/locales.txt");
	if (!loc_file)
		std::cerr << "Cannot open file!" << std::endl;
	else
	{
		for (std::string locale; std::getline(loc_file, locale); )
			// std::cout << locale << std::endl;
			show_currency_symbol(locale);
	}
	
	// show_currency_symbol("en_US.utf8");
	// show_currency_symbol("ja_JP.utf8");
	// show_currency_symbol("sv_SE.utf8");
	// show_currency_symbol("ru_RU.utf8");
	// show_currency_symbol("vi_VN.utf8");

	// system("pause");

	return EXIT_SUCCESS;
}