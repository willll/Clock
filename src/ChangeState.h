#pragma once

#include "Interfaces/IState.hpp"
#include "Interfaces/IObserver.hpp"
#include "Interfaces/IData.hpp"

#include <wiringPi.h>
#include <iostream>

#include "types.h"

class ChangeState : public IState, public IObserver<Types::frequency_t> {

	bool bStat;
	unsigned char nPin;

	public :
		explicit ChangeState(const unsigned char _nPin, const Types::frequency_t & _delay_ms) : 
			IState(_delay_ms),
			IObserver(),
			bStat(false),
			nPin(_nPin) {
				pinMode(nPin, OUTPUT); //Set the pin mode
				std::cout << "Using pin " << int(nPin) << std::endl;	//Output information on terminal
		}

		~ChangeState() {
			digitalWrite(nPin, LOW);
		}

		void operator()() {
			if (bStat) {
				digitalWrite(nPin, HIGH);
				//std::cout << "led turned ON" << std::endl;
			} else {
				digitalWrite(nPin, LOW);
				//std::cout << "led turned OFF" << std::endl;
			}
			bStat = !bStat;
		}

		virtual void update(const IData<Types::frequency_t> * _data) {
			setSleepDelay(_data->getState() + 1); // value between 1 and 256
		}
};