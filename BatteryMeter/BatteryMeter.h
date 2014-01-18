/*
||
|| @file 	BatteryMeter.cpp
|| @version	1.2
|| @author	Gus Michel
|| @contact	gus3@michelfamily.org
||
|| @description
|| | Provide an easy method of running an LED battery Meter/bar that 
|| | is charlieplexed
|| | Setup: 10k resistor from vin to Analog Pin, then another 10k resistor
|| | from the Analog Pin to Ground
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU General Public
|| | License as published by the Free Software Foundation; version
|| | 4 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | General Public License for more details.
|| |
|| | You should have received a copy of the GNU General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
||
*/
#ifndef BATTERYMETER_H
#define BATTERYMETER_H

#include "CharlieLed.h"
#include "TimeKeeper.h"
#include "Arduino.h"

class BatteryMeter {
	public:
		BatteryMeter(
			CharlieLed LEDs[],
			short numleds,
			short PINs[],
			short numpins,
			short vltpin,
			double fullVolt,
			double minVolt
		);
		void update();		//Recheck Voltage and reset Meter
		void off();		//Turn off all LEDs
	private:
		void light(short led);		//Light a specified LED
		CharlieLed *leds;		//Array of LEDs in a Charlieplex
		short numLeds;			//Number of Leds in array
		short *pins;			//Array of Pins the charlieplex is hooked into
		short numPins;			//Number of pins charlieplex is hooked into
		short voltagePin;		//Pin to read the voltage in through
		double max;			//Max/Full Voltage
		double min;			//Min Voltage
		
		double voltage;			//Current Voltage
		short numLightsOn;		//Number of LEDs that should be on
		
		TimeKeeper *stepTimer;		//Ups the CurrentStep
		unsigned long stepTime;		//Time Interval
		bool updateStep();		//Set the Step in the Battery Cycle
		short currentStep;
};
#endif
/*
|| @changelog
|| | 1.2 2012-05-24 - Gus Michel : Implemented Timing System for output
|| | 1.1 2012-05-23 - Gus Michel : Fixed Voltage Reading
|| | 1.0 2012-05-20 - Gus Michel : Initial Release
|| #
*/
