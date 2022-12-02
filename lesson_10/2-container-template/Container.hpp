#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

template <typename T>
class Container;

namespace std
{
    template <typename T>
    void std::swap(Container<T> &lhs, Container<T> &rhs);

    template <typename T>
    Container<T> *begin(Container<T> &container);

    template <typename T>
    Container<T> *end(Container<T> &container);

    template <typename T>
    constexpr Container<T> *begin(Container<T> const &container) noexcept;

    template <typename T>
    constexpr Container<T> *end(Container<T> const &container) noexcept;
}

template <typename T>
class Container
{
public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using size_type = std::size_t;
    using iterator = T *;
    using const_iterator = const T *;

    explicit Container(size_type size) : m_size(size), m_data(new value_type[size]) {}

    Container(const_pointer ptr, size_type size) : m_size(size), m_data(new value_type[size])
    {
        for (size_t i = 0; i < size; i++)
            m_data[i] = ptr[i];
    }

    Container(std::initializer_list<value_type> &&i_list) : m_size(std::size(i_list)), m_data(new value_type[m_size])
    {
        std::copy(std::begin(i_list), std::end(i_list), m_data);
    }

    Container(std::vector<value_type> const &vector) : m_size(vector.size()), m_data(new value_type[size])
    {
        for (size_t i = 0; i < m_size; i++)
            m_data[i] = vector[i];
    }

    Container(Container const &other) : m_size(other.m_size), m_data(new value_type[m_size])
    {
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }
    }

    Container(Container &&other) : m_size(other.m_size), m_data(other.m_data)
    {
        other.m_size = 0;
        other.m_data.release();
    }

    ~Container()
    {
        delete[] m_data;
    }

    iterator begin() noexcept
    {
        return m_data;
    }

    iterator end() noexcept
    {
        return std::next(m_data, m_size);
    }

    const_iterator begin() const noexcept
    {
        return m_data;
    }

    const_iterator end() const noexcept
    {
        return std::next(m_data, m_size);
    }

    const_reference operator[](size_type ind) const
    {
        if (ind >= m_size)
            throw std::out_of_range("Index out of range: " + std::to_string(ind) + " >= " + std::to_string(m_size));
        return m_data[ind];
    }

    reference operator[](size_type ind)
    {
        if (ind >= m_size)
            throw std::out_of_range("Index out of range: " + std::to_string(ind) + " >= " + std::to_string(m_size));
        return m_data[ind];
    }

    size_type size() const noexcept
    {
        return m_size;
    }

    friend void std::swap<value_type>(Container<value_type> &lhs, Container<value_type> &rhs);

    Container &resize(size_type new_size = m_size);

    Container &append(const_reference value)
    {
        resize(m_size + 1);
        m_data[m_size] = value;

        return *this;
    }

    Container &append(Container const &other);

    Container &pop()
    {
        if (m_size < 1)
            throw std::logic_error("Array didn't contains elements");
        resize(m_size - 1);
        return *this;
    }

    Container &reverse() noexcept
    {
        T *data = new T[m_size];
        for (size_t i = 0; i < m_size; i++)
            data[i] = m_data[i];
        for (size_t i = 0; i < m_size; i++)
            m_data[m_size - i - 1] = data[i];

        delete[] data;

        return *this;
    }

private:
    size_type m_size;
    value_type *m_data;
};

template <typename T>
std::ostream &operator<<(std::ostream &stream, Container<T> const &container)
{
    for (auto const &c : container)
        stream << c << " ";
    return stream;
}

template <typename T>
void std::swap(Container<T> &lhs, Container<T> &rhs)
{
    std::swap(lhs.m_data, rhs.m_data);
    std::swap(lhs.m_size, rhs.m_size);
}

template <typename T>
typename Container<T>::iterator std::begin(Container<T> &container)
{
    return container.begin();
}

template <typename T>
typename Container<T>::iterator std::end(Container<T> &container)
{
    return container.end();
}

template <typename T>
constexpr typename Container<T>::const_iterator std::begin(Container<T> const &container) noexcept
{
    return container.begin();
}

template <typename T>
constexpr typename Container<T>::const_iterator std::end(Container<T> const &container) noexcept
{
    return container.end();
}

template <typename T>
Container<T> &Container<T>::resize(typename Container<T>::size_type new_size)
{
    T *data = new T[m_size];
    for (size_t i = 0; i < m_size; i++)
        data[i] = m_data[i];

    m_data = new T[new_size];

    for (size_t i = 0; i < std::min(m_size, new_size); i++)
        m_data[i] = data[i];

    m_size = new_size;

    delete[] data;

    return *this;
}

template <typename T>
Container<T> &Container<T>::append(Container<T> const &other)
{
    size_t old_size = m_size;
    resize(m_size + other.m_size);
    for (size_t i = old_size; i < m_size; i++)
        m_data[i] = other.m_data[i - old_size];
    return *this;
}
