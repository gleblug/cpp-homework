#include <chrono>
#include <ratio>
#include "unistd.h"

#include <iostream>
#include <algorithm>
#include <vector>

#include <cassert>


namespace chrono = std::chrono;


enum class Period{sec, msec, usec, nsec};

class Timer
{
public:
  using clock_t = chrono::steady_clock;
  using duration_t = chrono::nanoseconds;
  using timepoint_t = chrono::time_point<clock_t, duration_t>;

  Timer() : is_enabled(false), m_time_before(0)
  {}

  void start()
  {
    if (!is_enabled)
    {
      m_start = clock_t::now();
      is_enabled = true;
    }
  }

  void stop()
  {
    if (is_enabled)
    {
      m_time_before += clock_t::now() - m_start;
      is_enabled = false;
    }
  }

  void restart()
  {
    stop();
    m_time_before = duration_t(0);
  }
  
  long long elapsed(Period format=Period::msec) const
  {
    auto time = m_time_before + (is_enabled ? (clock_t::now() - m_start) : duration_t(0));

    switch (format)
    {
      case Period::sec:
        return chrono::duration_cast<chrono::seconds>(time).count();
        break;

      case Period::msec:
        return chrono::duration_cast<chrono::milliseconds>(time).count();
        break;
      
      case Period::usec:
        return chrono::duration_cast<chrono::microseconds>(time).count();
        break;
      
      case Period::nsec:  
        return chrono::duration_cast<chrono::nanoseconds>(time).count();
        break;
      
      default:
        return 0;
    }
  }

private:
  bool is_enabled;
  timepoint_t m_start;
  duration_t m_time_before;
};

    
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