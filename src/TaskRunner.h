#pragma once

#include <iostream>
#include <thread>

#include "Interfaces/IState.hpp"

using namespace std::chrono_literals;


struct TaskRunner {

	explicit TaskRunner(IState & state_) :
		state_(state_),
		task_(nullptr)
	{ }
	
	~TaskRunner() {
		run_ = false;
		if (task_ && task_->joinable()) {
			task_->join();
		}
		delete task_;
		task_ = nullptr;
	}

	void run() {
		std::cout << "... Run" << std::endl;
		task_ = new std::thread(&TaskRunner::process, this);

		if (!task_) {
			throw std::runtime_error("new std::thread FAILED\n");
		}

		run_ = true;
	}

	void stop() {
		run_ = false;

		// wait whileit is stopping
        while (!stopped_) 
            std::this_thread::sleep_for(100ms);
	}

	private :

	void process() {
		while(run_) {
            stopped_ = false;
			state_();
			// TODO : change that with a condition variable
			std::this_thread::sleep_for(std::chrono::milliseconds(state_.getSleepDelay()));
		}
        stopped_ = true;
	}

	IState & state_;
	std::thread * task_;
	
	bool run_{false};
    bool stopped_{true};
};