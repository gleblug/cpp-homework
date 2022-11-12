#pragma once
#include <iterator>

template <typename T>
class ContainerIterator : public std::iterator<std::input_iterator_tag, T>
{
public:
    friend class OwnContainer;

    ContainerIterator(T *p_) : p(p_) {}

    ContainerIterator(ContainerIterator const &it) : p(it.p) {}

    bool operator!=(ContainerIterator const &other) const
    {
        return p != other.p;
    }

    typename ContainerIterator::reference operator*() const
    {
        return *p;
    }

    ContainerIterator & operator++()
    {
        std::advance(p, 1);
        return *this;
    }

private:
    T *p;
};