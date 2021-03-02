#include <wiringPi.h>

#include <iostream>
#include <chrono>
#include <csignal>
#include <deque>
#include <vector>
#include <atomic>
#include <algorithm>

#include "ChangeState.h"
#include "ReadState.h"
#include "TaskRunner.h"
#include "types.h"

using namespace std::chrono_literals;

const auto ledPin = 0;	//define the led pin number
const auto default_CPU_frequency_time = 400; // ms
const auto analog_port = 0;	//define the led pin number

Types::tasks_stack_t * tasks 	= nullptr;


/*
* signalHandler :
*	Stops threads,
*	Free up memory
*/
void signalHandler(int signum)
{
	std::cout << "Interrupt signal (" << signum << ") received.\n";

	std::for_each(
        tasks->begin(),
        tasks->end(),
        [](TaskRunner * task) {
            if (task)
				task->stop();
			delete task;
        });
	
	// terminate program
	std::cout << "... Exiting" << std::endl;

	exit(signum);
}

/*
* main
*	program entry point,
*	initialize resources,
*	start threads
*/
int main()
{	
	std::cout << "Program is starting ... \n";
	TaskRunner * oscillo 			= nullptr;
	TaskRunner * frequency_input 	= nullptr;
 	tasks = new Types::tasks_stack_t();

	//Types::atomic_frequency_t adcValue(CPU_frequency_time);

	// GPIO configuration
	wiringPiSetup();	//Initialize wiringPi.

	ChangeState gpio17(ledPin, default_CPU_frequency_time);
	ReadState 	clockValue(analog_port);
	
	oscillo = new TaskRunner(gpio17);
	frequency_input = new TaskRunner(clockValue);

	tasks->push_back (oscillo);
	tasks->push_back (frequency_input); 

	// mapping events
	clockValue.attach(&gpio17);

	// register signal handlers
	signal(SIGINT,  signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGKILL, signalHandler);
	signal(SIGQUIT, signalHandler);

	oscillo->run();
	frequency_input->run();

	std::cout << "Program is started ... \n";

	while(1) std::this_thread::sleep_for(1s);

	std::cout << "... Exiting" << std::endl;

	oscillo->stop();

	return EXIT_SUCCESS;
}
