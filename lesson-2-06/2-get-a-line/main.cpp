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

void create_file(const std::string &filename)
{
    std::ofstream fout(filename);
    std::ostream_iterator<std::string> oit(fout, "\n");

    const auto words = make_random_words();

    copy(cbegin(words), cend(words), oit);
}

int main(int argc, char const *argv[])
{
    const std::string filename = "words.txt";
    if ((!std::filesystem::exists(filename)) || (!std::filesystem::is_regular_file(filename)))
        create_file(filename);

    

    return 0;
}