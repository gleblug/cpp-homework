#pragma once
#include <vector>

template <typename T>
class container
{
public:
    container();

    container(std::vector<T> vector);
private:
    T *data;
    T *data_backup;
};