#include <ios>
#include <iostream>
#include <ostream>
#include <string>
#include <locale>
#include <iomanip>


using money_t = long double;

void converter(const std::string &locale1, const std::string locale2, const double exchange_rate)
{
	money_t input; 
	money_t output; 

	std::cin.imbue(std::locale(locale1));
	std::cin >> std::get_money(input);
	
	output = exchange_rate * input;

	std::cout.imbue(std::locale(locale2));
	std::cout << std::showbase << std::put_money(output, true) << std::endl;
}

enum class Options { EURtoRUB=1, RUBtoEUR=2 };

int main(int argc, char const *argv[])
{
	std::string welcome_message = "Welcome to the currency converter!\n1 -- EUR to RUB\n2 -- RUB to EUR";
	const double exchange_rate = 80.88;
	std::string localeEUR = "en_IE.utf8";
	std::string localeRUB = "ru_RU.utf8";

	std::cout << welcome_message << std::endl;
	uint opt_num;
	std::cin >> opt_num;
	Options option = static_cast<Options>(opt_num);

	switch (option) {
	case Options::EURtoRUB:
		converter(localeEUR, localeRUB, exchange_rate);
		break;
	case Options::RUBtoEUR:
		converter(localeRUB, localeEUR, 1.0/exchange_rate);
		break;
	}

	return 0;
}