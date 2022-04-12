#pragma once
#include <chrono>
class Stopwatch {
 public:
  using Clock = std::chrono::high_resolution_clock;
  using Time = uint64_t;
  Stopwatch() : start_point_(Clock::now()) {}
  auto tic() -> void { start_point_ = Clock::now(); }
  auto toc() const -> Time {
    //    std::atomic_thread_fence(std::memory_order_relaxed);
    auto counted_time = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - start_point_).count();
    //    std::atomic_thread_fence(std::memory_order_relaxed);
    return static_cast<Time>(counted_time);
  }

 protected:
  Clock::time_point start_point_;
};