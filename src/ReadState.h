#pragma once

#include "Interfaces/IState.hpp"
#include "Interfaces/ISubject.hpp"


#include <ADCDevice.hpp>
#include <iostream>

class ReadState : public IState, public ISubject<Types::frequency_t> {

	ADCDevice *adc_ = nullptr;
	const int nPort_;
	Types::frequency_t value_;

	public :
		ReadState(const int _nPort) :
			IState(1000),
			adc_(new ADCDevice()),
			nPort_(_nPort),
			value_(0) {
			if(adc_->detectI2C(0x48)) {    // Detect the pcf8591.
				delete adc_;                // Free previously pointed memory
				adc_ = new PCF8591();    // If detected, create an instance of PCF8591.
			}
			else if(adc_->detectI2C(0x4b)) {// Detect the ads7830
				delete adc_;               // Free previously pointed memory
				adc_ = new ADS7830();      // If detected, create an instance of ADS7830.
			}
			else {
				std::cout << "No correct I2C address found, \n";
				std::cout << "Please use command 'i2cdetect -y 1' to check the I2C address! \n";
				std::cout << "Program Exit. \n";
				exit(1);
			}
			// Initial value
			value_ = adc_->analogRead(nPort_);
		}

		~ReadState() {
		}

		void setState(const Types::frequency_t & _state) {
			value_ = _state;
		}

		Types::frequency_t getState() const {
			return value_;
		}

		void operator()() {
			auto adcValue = adc_->analogRead(nPort_);    // read analog value of A0 pin
			if (adcValue != value_) {
				value_ = adcValue;
				notify();
				printf("ADC value : %d\n", value_);
			}
		}
};
