#include <functional>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ctime>

template <typename T>
void merge_sort(
    T *array,
    std::size_t size, 
    std::function<bool(T, T)> comparator = [](T a, T b){ return a < b; }
) {
    if (size > 1)
    {
        std::size_t const left_size = size / 2;
        std::size_t const right_size = size - left_size;

        merge_sort(&array[0], left_size);
        merge_sort(&array[left_size], right_size);

        std::size_t left_ind = 0;
        std::size_t right_ind = left_size;
        std::size_t ind = 0;

        T* tmp_array = new T[size];

        while (left_ind < left_size || right_ind < size)
        {
            if (comparator(array[left_ind], array[right_ind]))
            {
                tmp_array[ind++] = std::move(array[left_ind]);
                left_ind++;
            }
            else
            {
                tmp_array[ind++] = std::move(array[right_ind]);
                right_ind++;
            }

            if (left_ind == left_size)
            {
                std::copy(&array[right_ind],
                          &array[size],
                          &tmp_array[ind]);
                break;
            }
            if (right_ind == size)
            {
                std::copy(&array[left_ind],
                          &array[left_size],
                          &tmp_array[ind]);
                break;
            }
        }

        std::copy(tmp_array,
                  &tmp_array[size],
                  array);

        delete [] tmp_array;
    }
}

int main(int argc, char const *argv[])
{
    std::srand(std::time(nullptr));

    // new array
    std::size_t size = 5;
    int *array = new int[size];

    // array out
    std::cout << "Array:" << std::endl;
    for (int* a = array; std::distance(array, a) < size; std::advance(a, 1))
    {
        *a = 1 + std::rand() / (static_cast<double>(RAND_MAX) / 100.0);
        std::cout << *a << " ";
    }
    std::cout << std::endl;

    // sort array
    merge_sort(array, size);

    // sorted array out
    std::cout << "Sorted array:\n";
    for (int *a = array; std::distance(array, a) < size; std::advance(a, 1))
    {
        std::cout << *a << " ";
    }
    std::cout << std::endl;

    return 0;
}
