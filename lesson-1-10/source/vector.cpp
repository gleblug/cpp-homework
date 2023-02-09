#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
// #include <xstring>

template < typename T >
class Vector
{
public:

	using value_type = T;
	using pointer = T * ;
	using const_pointer = const T *;
	using reference = T & ;
	using const_reference = const T &;
	using size_type = std::size_t;

	using iterator = pointer;
	using const_iterator = const_pointer;

public:

	Vector() = default;

	explicit Vector(size_type size);
	explicit Vector(size_type size, const T & initial); // = {10,10} -> (10,10)
	Vector(const Vector & other);
	Vector & operator=(const Vector &);


	~Vector() noexcept
	{
		delete[] m_data;
	}

public:

	reference operator[] (size_type index)
	{
		return m_data[index];
	}
	const_reference operator[](size_type index) const
	{
		return m_data[index];
	}

	reference front()
	{
		return m_data[0];
	}
	reference back()
	{
		return m_data[m_size - 1];
	}

	const_reference front() const
	{
		return m_data[0];
	}
	const_reference back() const
	{
		return m_data[m_size - 1];
	}

	iterator begin() noexcept
	{
		return m_data;
	}
	iterator end() noexcept
	{
		return m_data + m_size; // �� ������� ��������� �� ���������
	}

	const_iterator begin() const noexcept
	{
		return m_data;
	}
	const_iterator end() const noexcept
	{
		return m_data + m_size;
	}

	size_type size() const noexcept
	{
		return m_size;
	}
	size_type capacity() const noexcept
	{
		return m_capacity;
	}

	void push_back(const T & value);
	void pop_back()
	{
		m_size--;
	}

private:

	pointer m_data{ nullptr };
	size_type m_size{ 0 };
	size_type m_capacity{ 0 };
};

template < typename T >
Vector < T > ::Vector(size_type size) :
	m_size{size},
	m_capacity{size}
{
	m_data = new T[m_size];
}

template < typename T >
Vector < T > ::Vector(size_type size, const T & initial) :
	m_size{size},
	m_capacity{size}
{
	m_data = new T[m_size];
	for (std::size_t i = 0; i < m_size; ++i)
		m_data[i] = initial;
}

template < typename T >
Vector < T >::Vector(const Vector < T > & other) :
	m_size{ other.m_size },
	m_capacity{ other.m_capacity }
{
	m_data = new T[m_size];
	std::copy(other.begin(), other.end(), m_data);
}

template < typename T >
Vector < T > & Vector < T > ::operator= (const Vector<T>& other)
{
	if (this == &other) return *this;
	delete[] m_data;

	m_size = other.m_size;
	m_capacity = other.m_other;
	m_data = new T[m_size];

	std::copy(other.begin(), other.end(), m_data);
	return *this;
}

template < typename T >
void Vector<T>::push_back(const T & value)
{
	if (m_size >= m_capacity)
	{
		auto new_capacity = m_capacity == 0 ? 1 : 2 * m_capacity;
		auto new_data = new T[new_capacity];
		std::copy(this->begin(), this->end(), new_data);
		delete[] m_data;
		m_data = new_data;
		m_capacity = new_capacity;
	}
	m_data[m_size++] = value;
}

#include <type_traits>

template < typename D, typename B >
class Is_Derived
{
	class No {};
	class Yes { No no[2]; }; // ������ �������� !

	static Yes test(B*);
	static No test(...); // ������. ���������� ���������� ����������� �����

public:

	// ���������� ���������� ����������� �� ����� ����������
	// ����������� �������� sizeof ����������� �� ����� ����������
	// �������� � enum ����������� �� ����� ����������

	enum { value = sizeof(test(static_cast<D*>(0))) == sizeof(Yes) };
};

class B {};
class D : public B {};
class DD : public D {};
class E {};

int main(int argc, char ** argv)
{
	std::cout << std::boolalpha;

	std::cout << std::is_base_of < B, D > ::value << std::endl;
	std::cout << std::is_base_of_v < B, DD > << std::endl;
	std::cout << std::is_base_of_v < B, E > << std::endl;

	std::cout << Is_Derived < D, B > ::value << std::endl;
	std::cout << Is_Derived < DD, B > ::value << std::endl;
	std::cout << Is_Derived < E, B > ::value << std::endl;

	Vector < int > v;

	assert(v.capacity() == 0);

	Vector<std::string> v1(2);
	assert(v1.capacity() == 2);
	assert(v1.size() == 2);
	assert(v1[0] == "");
	assert(v1[1] == "");

	v1[0] = "hi";
	assert(v1[0] == "hi");

	Vector<int> v2(2, 7);
	assert(v2[1] == 7);

	Vector<int> v10(v2);
	assert(v10[1] == 7);

	Vector<std::string> v3(2, "hello");
	assert(v3.size() == 2);
	assert(v3.capacity() == 2);
	assert(v3[0] == "hello");
	assert(v3[1] == "hello");

	Vector < std::string > v4 = v3;

	assert(v4[0] == v3[0]);
	v3[0] = "test";
	assert(v4[0] != v3[0]);
	assert(v4[0] == "hello");

	v3.pop_back();
	assert(v3.size() == 1);

	Vector < int > v5(7, 9);
	Vector < int > ::iterator it = v5.begin();
	while (it != v5.end())
	{
		assert(*it == 9);
		++it;
	}

	Vector < int > v6;
	v6.push_back(100);
	assert(v6.size() == 1);
	assert(v6[0] == 100);
	v6.push_back(101);
	assert(v6.size() == 2);
	assert(v6[0] == 100);
	v6.push_back(101);

	std::cout << "SUCCESS\n";

	system("pause");

	return EXIT_SUCCESS;
}

