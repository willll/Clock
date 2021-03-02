#pragma once

#include <atomic>
#include <deque>

// Forward declarations
struct TaskRunner;

namespace Types {

    typedef unsigned int                                frequency_t;
    typedef std::deque<TaskRunner *>                    tasks_stack_t;

}
