#include <boost/locale/encoding_utf.hpp>
#include <codecvt>
#include <iostream>
#include <ostream>
#include <string>
#include <map>

#include <boost/locale/encoding.hpp>
#include <boost/locale.hpp>
#include <string_view>


using u32string = std::basic_string<char32_t>;

std::string locale_to_utf8(const std::string & string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char >(string, locale);
}

std::string utf8_to_locale(const std::string & string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char >(string, locale);
}

u32string utf8_to_utf32(const std::string &string)
{
	return boost::locale::conv::utf_to_utf<char32_t>(string);
}

std::string utf32_to_utf8(const u32string &string)
{
	return boost::locale::conv::utf_to_utf<char>(string);
}


template <typename CharT>
void print_string(const std::basic_string<CharT> &string)
{
	for (const auto c : string)
		std::cout << static_cast<uint>(c) << ' ';
	std::cout << std::endl;
}


int main(int argc, char const *argv[])
{
	std::unordered_map<char32_t, char32_t> transliterate_table{
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

	std::string utf8_input = locale_to_utf8(locale_input);
	u32string utf32_input = utf8_to_utf32(utf8_input);

	u32string utf32_output(utf32_input.size(), ' ');
	for (size_t i = 0; i < utf32_output.size(); ++i)
		utf32_output[i] = transliterate_table[utf32_input[i]];

	std::string utf8_output = utf32_to_utf8(utf32_output);
	std::string locale_output = utf8_to_locale(utf8_output);

	std::cout << "\nTransliterated message:\n" << locale_output << std::endl;

	return 0;
}