#include <chrono>
#include <ratio>

namespace chrono = std::chrono;

enum class Period{sec, msec, usec, nsec};

class Timer
{
public:
  using clock_t = chrono::steady_clock;
  using duration_t = chrono::nanoseconds;
  using timepoint_t = chrono::time_point<clock_t, duration_t>;
  using time_t = unsigned long long; 

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
  
  time_t elapsed(Period format=Period::msec) const
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