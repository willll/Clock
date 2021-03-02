#pragma once

#include "types.h"

#include <mutex>

// forward declarations
struct TaskRunner;


class IState {

    Types::frequency_t delay_ms_;
    std::mutex mutex_;

public :

    explicit IState(const Types::frequency_t & _delay_ms) :
        delay_ms_(_delay_ms)
    { }

    virtual void setSleepDelay(const Types::frequency_t & _delay_ms) {
        std::lock_guard<std::mutex> guard(mutex_);
        delay_ms_ = _delay_ms;
    }

    virtual Types::frequency_t getSleepDelay() {
        std::lock_guard<std::mutex> guard(mutex_);
        return delay_ms_;
    }

    virtual void operator()() = 0;
};
