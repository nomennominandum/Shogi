#include <iostream>
#include <atomic>
#include <chrono>
#include <string>

std::chrono::steady_clock::duration 
atomic_fetch_add(std::atomic<std::chrono::steady_clock::duration> *pta, 
                      std::chrono::steady_clock::duration d,
                      std::memory_order mo) {
  auto prev = pta->load(std::memory_order_relaxed);
  while (not pta->compare_exchange_weak(prev, prev+d, mo, std::memory_order_relaxed)) {}
  return prev;
}

template <typename print_duration=std::chrono::milliseconds>
struct Timer {
  using clock = std::chrono::steady_clock;
  using duration = clock::duration;
  using time_point = clock::time_point;
  std::atomic<duration> dur{};
  std::string name;
  Timer(std::string name) : name(std::move(name)) {}
  struct LifeTime {
    Timer& timer;
    time_point tp;
    LifeTime(Timer& t) : timer(t), tp(clock::now()) {}
    ~LifeTime() { 
      auto dt = clock::now()-tp; 
      atomic_fetch_add(&timer.dur, dt, std::memory_order_relaxed); 
    }
  };
  LifeTime operator ()() { return LifeTime(*this); }
  ~Timer() {
     std::cout << name << " took "
               << std::chrono::duration_cast<print_duration>(dur.load(std::memory_order_relaxed)).count() 
               << std::endl;
  }
};

