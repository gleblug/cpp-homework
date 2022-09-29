#include <iostream>
#include <vector>
#include <sstream>
#include <string>

//  Left source half is   A[ iBegin:iMiddle-1].
// Right source half is   A[iMiddle:iEnd-1   ].
// Result is              B[ iBegin:iEnd-1   ].
void TopDownMerge(std::vector<int> &A, size_t iBegin, size_t iMiddle, size_t iEnd, std::vector<int> &B)
{
    size_t i = iBegin;
    size_t j = iMiddle;

    for (size_t k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A.at(i) <= A.at(j))) {
            B.at(k) = A.at(i);
            i = i + 1;
        } else {
            B.at(k) = A.at(j);
            j = j + 1;
        }
    }
}

void mergeSort(std::vector<int> &B, size_t iBegin, size_t iEnd, std::vector<int> &A)
{
    if (iEnd - iBegin <= 1) {
      return;
    }

    size_t iMiddle = (iEnd + iBegin) / 2;       // iMiddle = mid point
    // recursively sort both runs from array A[] into B[]
    mergeSort(A, iBegin, iMiddle, B);           // sort the left  run
    mergeSort(A, iMiddle, iEnd, B);             // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge(B, iBegin, iMiddle, iEnd, A);
}

void userInput(std::vector<int> &array)
{
  std::cout << "\x1B[36m" << "Input an array of INTEGERS (splitter = ' '):" << "\033[0m" << std::endl;

  // Declaring variables
  std::string input;
  std::stringstream streamInput;

  int elem;
  std::string wrongElem;

  // Get first line from input stream to string 'input'
  std::getline(std::cin, input);

  // Push 'input' to string stream
  streamInput << input;

  // Push every elem from streamInput to array as integer while it's not empty
  while (streamInput >> elem) {
    array.push_back(elem);
  }
  std::cout << std::endl;
}

void userOutput(std::vector<int> const &array)
{
  std::cout << "\x1B[32m" << "Sorted array:" << "\033[0m" << std::endl;

  for (int const &elem: array) {
    std::cout << elem << " ";
  }

  std::cout << '\n' << std::endl;
}

int main(int argc, char const *argv[])
{
  // Declaring variables
  std::vector<int> array;

  // User input
  userInput(array);

  // Merge sort
  std::vector<int> array_copy(array);
  mergeSort(array, 0, array.size(), array_copy);

  // Print result
  userOutput(array_copy);

  // Exit program successfully
  return 0;
}
