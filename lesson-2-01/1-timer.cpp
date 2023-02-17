#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

#include "unistd.h"
#include "timer.hpp"

    
void sort(std::vector < int > & v)
{
  for (std::size_t i = 0; i < v.size() - 1; ++i)
  {
    for (std::size_t j = i + 1; j < v.size(); ++j)
    {
      if (v[i] > v[j])
      {
        std::swap(v[i], v[j]);
      }
    }
  }
}

void test_sort_time()
{
  std::cout << "Sorting 10_000 elements...\n";
  const auto size = 10000U;

  std::vector < int > v(size, 0);

  for (std::size_t i = 0; i < v.size(); ++i)
  {
    v[i] = v.size() - i;
  }

  auto v_1 = v;
  auto v_2 = v;

  sort(v_1);

  Timer timer;
  timer.start();

  std::sort(v_2.begin(), v_2.end());

  timer.stop();

  std::cout << "sort complete for " << timer.elapsed(Period::usec) << " (microseconds)" << std::endl;
}


void test_timer()
{
  std::cout << "Start testing..." << std::endl;
  Timer timer;
  assert(timer.elapsed() == 0);

  timer.start();
  usleep(3000);
  timer.stop();

  assert(timer.elapsed() == 3);

  usleep(5000);
  
  assert(timer.elapsed() == 3);

  timer.start();
  usleep(4000);
  timer.stop();

  assert(timer.elapsed() == 7);

  timer.restart();

  assert(timer.elapsed() == 0);

  std::cout << "Tests complete!\n" << std::endl;
}

int main(int argc, char const *argv[])
{
  test_timer();

  test_sort_time();

  return 0;
}