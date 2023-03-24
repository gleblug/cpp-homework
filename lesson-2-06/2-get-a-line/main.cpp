#include <algorithm>
#include <iostream>
#include <string>
#include <iterator>
#include <set>
#include <random>
#include <chrono>
#include <fstream>
#include <filesystem>

std::set < std::string > make_random_words(std::size_t N = 1000, std::size_t length = 10)
{
    std::uniform_int_distribution <> letter(97, 122);
    std::default_random_engine e(static_cast < std::size_t > (
        std::chrono::system_clock::now().time_since_epoch().count()));

    std::set < std::string > words;

    for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
        for (auto & c : s)
            c = letter(e);

    return words;
}

void create_file(const std::string &filename, const size_t number_of_words, const size_t word_length)
{
    std::ofstream fout(filename);
    std::ostream_iterator<std::string> fout_iter(fout, "\n");

    const auto words = make_random_words(number_of_words, word_length);

    copy(cbegin(words), cend(words), fout_iter);
}

int main(int argc, char const *argv[])
{
    const std::string filename = "words.txt";
    const size_t number_of_words = 1000;
    const size_t word_length = 10;

    if ((!std::filesystem::exists(filename)) || (!std::filesystem::is_regular_file(filename)))
        create_file(filename, number_of_words, word_length);

    std::ifstream fin(filename);
    std::string word;
    size_t line_number;

    std::cout << "Enter a line number (1-" << number_of_words << "):" << std::endl;

    while (std::cin) 
    {
        std::cin >> line_number;
        fin.seekg((line_number - 1) * (word_length + 1));
        fin >> word;
        std::cout << word << std::endl;
    }

    return 0;
}