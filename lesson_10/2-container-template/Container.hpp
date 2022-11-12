#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include "ContainerIterator.hpp"

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
    typedef ContainerIterator<T> iterator;
    typedef ContainerIterator<const T> const_iterator;
    

    explicit Container(size_t size) : m_size(size), m_data(new T[size]) {}

    Container(T* const&ptr, size_t size) : m_size(size), m_data(new T[size])
    {
        for (size_t i = 0; i < size; i++)
            m_data[i] = ptr[i];
    }

    Container(T* &&ptr, size_t size) : m_size(size), m_data(ptr)
    {
        ptr = nullptr;
    }

    Container(std::initializer_list<T> &&i_list) : m_size(std::size(i_list)), m_data(new T[m_size])
    {
        std::copy(std::begin(i_list), std::end(i_list), m_data.get());
    }

    Container(std::vector<T> const &vector) : m_size(vector.size()), m_data(new T[size])
    {
        for (size_t i = 0; i < m_size; i++)
            m_data[i] = vector[i];
    }

    Container(Container const &other) : m_size(other.m_size), m_data(new T[m_size])
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

    iterator begin() noexcept
    {
        return iterator(m_data.get());
    }

    iterator end() noexcept
    {
        return iterator(std::next(m_data.get(), m_size));
    }

    const_iterator begin() const noexcept
    {
        return const_iterator(m_data.get());
    }

    const_iterator end() const noexcept
    {
        return const_iterator(std::next(m_data.get(), m_size));
    }

    const T& operator[](std::size_t ind) const
    {
        if (ind >= m_size)
            throw std::out_of_range("Index out of range: " + std::to_string(ind) + " >= " + std::to_string(m_size));
        return m_data[ind];
    }

    T& operator[](std::size_t ind)
    {
        if (ind >= m_size)
            throw std::out_of_range("Index out of range: " + std::to_string(ind) + " >= " + std::to_string(m_size));
        return m_data[ind];
    }

    size_t size() const noexcept
    {
        return m_size;
    }

    friend void std::swap<T>(Container<T> &lhs, Container<T> &rhs);

    Container &resize(size_t new_size);

    Container &append(T const &value)
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
        std::unique_ptr<T[]> data(new T [m_size]);
        for (size_t i = 0; i < m_size; i++)
            data[i] = m_data[i];
        for (size_t i = 0; i < m_size; i++)
            m_data[m_size - i - 1] = data[i];
        
        return *this;
    }

private:
    size_t m_size;
    std::unique_ptr<T[]> m_data;
};

template <typename T>
std::ostream &operator<<(std::ostream &stream, Container<T> const &container)
{
    for (auto const &c: container)
        stream << c << " ";
    return stream;
}

template <typename T>
void std::swap(Container<T> &lhs, Container<T> &rhs)
{
    size_t lhs_size = lhs.m_size;
    std::unique_ptr<T[]> lhs_data = lhs.m_data;

    lhs.m_size = rhs.m_size;
    lhs.m_data = rhs.m_data;

    rhs.m_size = lhs_size;
    rhs.m_data = lhs_data;
}

template <typename T>
Container<T> *std::begin(Container<T> &container)
{
    return container.begin();
}

template <typename T>
Container<T> *std::end(Container<T> &container)
{
    return container.end();
}

template <typename T>
constexpr Container<T> *std::begin(Container<T> const &container) noexcept
{   
    return container.begin();
}

template <typename T>
constexpr Container<T> *std::end(Container<T> const &container) noexcept
{   
    return container.end();
}

template <typename T>
Container<T> &Container<T>::resize(size_t new_size)
{
    std::unique_ptr<T[]> data(new T[m_size]);
    for (size_t i = 0; i < m_size; i++)
        data[i] = m_data[i];

    m_data = std::unique_ptr<T[]>(new T [new_size]);

    for (size_t i = 0; i < std::min(m_size, new_size); i++)
        m_data[i] = data[i];

    m_size = new_size;

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
