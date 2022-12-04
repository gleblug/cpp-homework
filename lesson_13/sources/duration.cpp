#include <iostream>

template <int N, int D = 1>
struct Ratio
{
	static constexpr int num = N;
	static constexpr int den = D;

	using type = Ratio<num, den>;
};

template <typename R1, typename R2>
class Ratio_Add_Implementaion
{
private:
	static constexpr int den = R1::den * R2::den;
	static constexpr int num = R1::num * R2::den + R2::num * R1::den;

public:
	using type = Ratio<num, den>;
};

template <typename R1, typename R2>
using Ratio_Add = typename Ratio_Add_Implementaion<R1, R2>::type;

template <typename T, typename U = Ratio<1>>
class Duration
{
public:
	using value_t = T;

public:
	constexpr Duration(value_t value = 0) noexcept
		: m_value(value)
	{
	}

	~Duration() noexcept = default;

public:
	constexpr auto value() const noexcept
	{
		return m_value;
	}

private:
	value_t m_value;
};

template <typename T1, typename U1, typename T2, typename U2>
auto constexpr operator+(
	const Duration<T1, U1> &lhs,
	const Duration<T2, U2> &rhs)
{
	using VT = Ratio<1, Ratio_Add<U1, U2>::den>;

	auto value =
		lhs.value() * VT::den / U1::den * U1::num +
		rhs.value() * VT::den / U2::den * U2::num;

	return Duration<decltype(value), VT>(value);
}

int main(int argc, char **argv)
{
	std::cout << (Duration<int, Ratio<2, 5>>(3) +
				  Duration<int, Ratio<1, 7>>(6))
					 .value()
			  << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}