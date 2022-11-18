#include <functional>
#include <iostream>
#include <iterator>
#include <random>

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
    // random integers generator
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    auto rand = [&]()->int { return dist(mt); };

    // new array
    const std::size_t size = 5; // ARRAY SIZE
    int *dyn_array = new int[size];
    int stat_array[size];

    // array out
    std::cout << "Array:" << std::endl;
    for (size_t i = 0; i < size; i++)
    {
        int a = rand();
        dyn_array[i] = a;
        stat_array[i] = a;

        std::cout << a << ' ';
    }
    std::cout << std::endl;

    // sort array
    merge_sort(dyn_array, size);

    // sorted array out
    std::cout << "\nSorted dyn array:\n";
    for (size_t i = 0; i < size; i++)
        std::cout << dyn_array[i] << ' ';    
    std::cout << std::endl;

    std::cout << "\nSorted stat array:\n";
    for (size_t i = 0; i < size; i++)
        std::cout << stat_array[i] << ' ';
    std::cout << std::endl;

    return 0;
}
