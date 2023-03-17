#include <codecvt>
#include <iostream>
#include <ostream>
#include <string>
#include <map>

#include <boost/locale/encoding.hpp>
#include <boost/locale.hpp>


std::string convert_locale_to_utf(const std::string & string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char >(string, locale);
}

std::string convert_utf_to_locale(const std::string & string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char >(string, locale);
}

std::wstring convert_utf8_to_wstring(const std::string & string)
{
	std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter;
	return converter.from_bytes(string);
}

std::string convert_wstring_to_utf8(const std::wstring & wstring)
{
	std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter;
	return converter.to_bytes(wstring);
}


int main(int argc, char const *argv[])
{
	std::map<wchar_t, wchar_t> transliterate_table{
		{L'а', 'a'},
		{L'б', 'b'},
		{L'в', 'v'},
		{L'г', 'g'},
		{L'д', 'd'},
		{L'е', 'e'},
		{L'ё', 'e'},
		{L'ж', 'z'},
		{L'з', 'z'},
		{L'и', 'i'},
		{L'й', 'i'},
		{L'к', 'k'},
		{L'л', 'l'},
		{L'м', 'm'},
		{L'н', 'n'},
		{L'о', 'o'},
		{L'п', 'p'},
		{L'р', 'r'},
		{L'с', 's'},
		{L'т', 't'},
		{L'у', 'u'},
		{L'ф', 'f'},
		{L'х', 'h'},
		{L'ц', 'c'},
		{L'ч', 'c'},
		{L'ш', 's'},
		{L'щ', 's'},
		{L'ъ', 'e'},
		{L'ы', 'i'},
		{L'ь', '\''},
		{L'э', 'e'},
		{L'ю', 'u'},
		{L'я', 'a'},
		{L' ', ' '}
	};

	std::cout << "Enter a message:\n";

	std::string locale_input;
	std::getline(std::cin, locale_input);

	std::string utf8_input = convert_locale_to_utf(locale_input);
	std::wstring utf32_input = convert_utf8_to_wstring(utf8_input);

	std::wstring utf32_output(utf32_input.size(), ' ');
	for (size_t i = 0; i < utf32_output.size(); ++i)
		utf32_output[i] = transliterate_table[utf32_input[i]];

	std::string utf8_output = convert_wstring_to_utf8(utf32_output);
	std::string locale_output = convert_utf_to_locale(utf8_output);

	std::cout << "\nTransliterated message:\n" << locale_output << std::endl;

	return 0;
}