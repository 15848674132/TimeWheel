#ifndef TIMEWHEEL_H
#define TIMEWHEEL_H

#include <chrono>
#include <string>
#include <memory>
#include <vector>
#include <list>

#include "timer.h"

class TimeWheel {
public:
    TimeWheel(uint32_t scales, uint32_t scale_uint_ms, const std::string name = "");
    ~TimeWheel() = default;
    uint32_t scale_unit_ms() const { return scale_unit_ms_; }

    uint32_t scales() const { return scales_; }

    uint32_t current_index() const { return current_index_; }

    void set_less_level_tw(TimeWheel *less_level_tw) { less_level_tw_ = less_level_tw; }

    void set_greater_level_tw(TimeWheel *greater_level_tw) { greater_level_tw_ = greater_level_tw; }

    int64_t GetCurrentTime() const;

    void AddTimer(TimerPtr timer);

    void Increase();

    std::list<TimerPtr> GetAndClearCurrentSlot();

private:
    std::string name_;
    uint32_t current_index_;

    uint32_t scales_;
    uint32_t scale_unit_ms_;

    std::vector<std::list<TimerPtr>> slots_;

    TimeWheel *less_level_tw_;
    TimeWheel *greater_level_tw_;
};


using TimeWheelPtr = std::shared_ptr<TimeWheel>;

static inline int64_t GetNowTimestamp() {
    using namespace std::chrono;
    auto now = system_clock::now().time_since_epoch();
    return duration_cast<milliseconds>(now).count();
}

#endif