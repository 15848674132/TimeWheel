#ifndef TIMER_H
#define TIMER_H

#include <cstdint>
#include <functional>
#include <memory>

/**
 * 
*/


using TimerTask_t = std::function<void()>;

class Timer {
public:
    Timer(uint32_t id, int64_t when_ms, int64_t interval_ms, const TimerTask_t& task);
    ~Timer() = default;
    void Run();
    uint32_t id() const { return id_; }
    int64_t when_ms() const { return when_ms_; }
    int64_t repeated() const { return repeated_; }
    void UpdateWhenTime() { when_ms_ += interval_ms_; }
private:
    uint32_t id_;
    TimerTask_t task_;
    int64_t when_ms_;
    uint32_t interval_ms_;
    bool repeated_;
};

using TimerPtr = std::shared_ptr<Timer>;
#endif