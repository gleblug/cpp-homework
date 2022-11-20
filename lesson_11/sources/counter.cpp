#include <cstddef>
#include <iostream>

template < typename T >
class Counter 
{
protected:

	Counter() noexcept
	{
		++m_counter;
	}

	Counter(const Counter < T > &) noexcept
	{
		++m_counter;
	}

	Counter(Counter < T > &&) noexcept
	{
		++m_counter;
	}

	~Counter() noexcept
	{
		--m_counter;
	}

public:

	static const auto counter() noexcept
	{
		return m_counter;
	}

private:

	inline static std::size_t m_counter = 0;

};

template < typename T >
class String_1 : public Counter < String_1 < T > > 
{};

template < typename T >
class String_2 : public Counter < String_2 < T > >
{};

int main(int argc, char ** argv)
{	
	{
		String_1 < char > s1, s2;
		String_2 < wchar_t > ws;

		std::cout << "counter of String_1 < char >    : " << String_1 < char > ::counter() << std::endl;
		std::cout << "counter of String_2 < wchar_t > : " << ws.counter() << std::endl;
	}
	std::cout << "counter of String_1 < char >    : " << String_1<char>::counter() << std::endl;
	std::cout << "counter of String_2 < wchar_t > : " << String_2<wchar_t>::counter() << std::endl;
	return EXIT_SUCCESS;
}