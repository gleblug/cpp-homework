#include <iostream>

template <int p, int d>
struct Check_Is_Prime
{
	static const bool value = (p % d != 0) && Check_Is_Prime<p, d - 1>::value;
};

template <int p>
struct Check_Is_Prime<p, 2>
{
	static const bool value = (p % 2 != 0);
};

template <int p>
struct Is_Prime
{
	static const bool value = Check_Is_Prime<p, p / 2>::value;
};

template <>
struct Is_Prime<0>
{
	static const bool value = false;
};

template <>
struct Is_Prime<1>
{
	static const bool value = false;
};

template <>
struct Is_Prime<2>
{
	static const bool value = true;
};

template <>
struct Is_Prime<3>
{
	static const bool value = true;
};

/*
constexpr bool check_is_prime(int p, int d) // C++11
{
	return (d != 2) ? (p % d != 0) && check_is_prime(p, d - 1) : (p % 2 != 0);
}

constexpr bool is_prime(int p)
{
	return (p < 4) ? !(p < 2) : check_is_prime(p, p / 2);
}
*/

constexpr bool is_prime(int p) // C++14
{
	for (int d = 2; d <= p / 2; ++d)
	{
		if (p % d == 0)
		{
			return false;
		}
	}

	return p > 1;
}

int main(int argc, char **argv)
{
	constexpr bool result = Is_Prime<537>::value; // compile-time result

	// constexpr bool result = is_prime(x);

	std::cout << std::boolalpha << result << std::endl;

	return EXIT_SUCCESS;
}