#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>

auto get_sieve_of_eratosthenes(size_t n)
{
    std::vector<bool> A(n, true);
    for(size_t i = 2; i <= std::floor(sqrt(n)); ++i)
        if (A[i])
        {
            size_t j = i * i;
            while(j <= n)
            {
                A[j] = false;
                j += i;
            }
        }
    A[0] = A[1] = false;
    return A;
}

int main(int argc, char const *argv[])
{
    using elem_t = int;
    using p_t = std::vector<elem_t>;

    auto print = [](const std::string &message, const p_t &p)
    {
        static size_t id = 1;
        std::cout 
            << std::left << std::setw(50) 
            << "@" + std::to_string(id) + " " + message
            << std::right;
        std::copy(begin(p), end(p), std::ostream_iterator<elem_t>(std::cout, " "));
        std::cout << "\n";
        ++id;
    };

    std::random_device rand_dev;
    std::mt19937_64 gen(rand_dev());
    std::uniform_int_distribution<elem_t> distr(-20, 20);
    auto get_rand = [&distr, &gen](){ return distr(gen); };


    // @1 : fill vector p1 {1..10} 
    p_t p1(10);
    iota(begin(p1), end(p1), elem_t(1));
    print("fill", p1);
    
    // @2 : add some elems from std::cin
    std::istream_iterator<elem_t> in_first(std::cin);
    std::istream_iterator<elem_t> in_last{};
    copy(in_first, in_last, back_inserter(p1));
    print("add", p1);

    // @3 : random shuffle
    shuffle(begin(p1), end(p1), gen);
    print("shuffle", p1);

    // @4 : remove duplicates
    sort(begin(p1), end(p1));
    auto it_last = unique(begin(p1), end(p1));
    p1.erase(it_last, end(p1));
    print("unique", p1);

    // @5 : count of odd
    auto odd = [](elem_t i){ return i % 2; };
    const auto odd_count = count_if(cbegin(p1), cend(p1), odd);
    print("odd count = " + std::to_string(odd_count), p1);

    // @6 : min & max
    const auto [it_min, it_max] = minmax_element(cbegin(p1), cend(p1));
    print("min, max = " + std::to_string(*it_min) + " " + std::to_string(*it_max), p1);

    // @7 : prime number
    const elem_t max = *it_max;
    auto is_prime = [&max](elem_t value)
    {
        static const auto sieve_of_eratosthenes = get_sieve_of_eratosthenes(max);       
        return sieve_of_eratosthenes.at(value);
    };
    auto result = find_if(cbegin(p1), cend(p1), is_prime);
    (result != end(p1)) 
        ? print("prime number = " + std::to_string(*result), p1)
        : print("no prime numbers", p1);

    // @8 : square elems
    auto sqr = [](elem_t value){ return value * value; };
    transform(cbegin(p1), cend(p1), begin(p1), sqr);
    print("sqr of elems", p1);

    // @9 : fill vector p2 randomly
    p_t p2(p1.size());
    generate(begin(p2), end(p2), get_rand);
    print("p2", p2);

    // @10 : summ of p2
    auto summ = accumulate(cbegin(p2), cend(p2), 0);
    print("summ of p2 = " + std::to_string(summ), p2);

    // @11 : replace first 3 elems to ones
    fill(begin(p2), next(begin(p2), 3), 1);
    print("replace first 3 elems to ones", p2);

    // @12 : p3 = p1 - p2
    p_t p3(p1.size());
    auto diff = [](const elem_t a, const elem_t b){ return a - b; };
    transform(cbegin(p1), cend(p1), cbegin(p2), begin(p3), diff);
    print("p3 = p1 - p2", p3);

    // @13 : replace negative to zeros in p3
    auto is_negative = [](elem_t value){ return value < 0; };
    replace_if(begin(p3), end(p3), is_negative, 0);
    print("replace negatives to zeros", p3);

    // @14: remove zeros
    auto is_zero = [](elem_t value){ return value == 0; };
    auto last = remove_if(begin(p3), end(p3), is_zero);
    p3.erase(last, end(p3));
    print("remove all zeros", p3);

    // @15 : reverse p3
    reverse(begin(p3), end(p3));
    print("reverse p3", p3);

    // @16 : top-3 elems
    nth_element(begin(p3), next(begin(p3)), end(p3), std::greater<elem_t>{});
    p_t top3;
    copy(begin(p3), next(begin(p3), 3), back_inserter(top3));
    print("top3 ", top3);

    // @17 : sort p1 & p2
    sort(begin(p1), end(p1));
    sort(begin(p2), end(p2));
    print("sort p1, p2", {});

    // @18 : union p1, p2
    p_t p4;
    p4.reserve(p1.size() + p2.size());
    merge(cbegin(p1), cend(p1), cbegin(p2), cend(p2), back_inserter(p4));
    print("p4 = merge p1 & p2", p4);

    // @19 : range to insert 1
    auto [first_one, last_one] = std::equal_range(cbegin(p4), cend(p4), 1);
    size_t first_one_idx = distance(cbegin(p4), first_one);
    size_t last_one_idx = distance(cbegin(p4), last_one);
    print("insert one between " + std::to_string(first_one_idx) + " and " + std::to_string(last_one_idx), p4);

    // @20 : print p1, p2, p3, p4
    print("p1", p1);
    print("p2", p2);
    print("p3", p3);
    print("p4", p4);

    return 0;
}
