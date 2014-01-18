/*
||
|| @file 	CharliePulser.cpp
|| @version	1.2
|| @author	Gus Michel
|| @contact	gus3@michelfamily.org
||
|| @description
|| | Provide an system for running an array of Charlieplexed LEDs 
|| | for pulsing and displays (usually linear)
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU General Public
|| | License as published by the Free Software Foundation; version
|| | 3 of the License.
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
#ifndef CHARLIEPULSER_H
#define CHARLIEPULSER_H


#include <math.h>
#include "CharlieLed.h"
#include "Arduino.h"
#include "TimeKeeper.h"


class CharliePulser {
	public:
	    	CharliePulser(
			CharlieLed LEDs[],
			short numleds,
			short PINs[],
			short numpins,
			short mode,
			unsigned long time
	    	);//CONSTRUCTOR
		void setTime(int time);			//Set Timer between steps
		void checkTimers();			//Check Timers (for Timeing of LED steps and Pulsing of multipule LEDs)
		void setMode(short mode);		//Set Current Mode
		void off();				//Turn off all LEDs
		void on();				//Turn on "All" LEDs
	private:
		short currentStep;			//The Current Step in the Mode (to allow for timing)
		short currentLed;			//The Current LED (for pulsing multipule LEDs back and forth)
		short currentMode;			//The number of the current operation to be performed
		
		
		unsigned long stepTime;			//The Time per step
		unsigned long ledTime;			//The Time between rerunning the current LED
		unsigned long modeTime;			//The Time between rerunning the current step
		
		CharlieLed *leds;			//Array of CharlieLeds in the CharliePulser
		short numLeds;				//The Number of LEDs in the array
		short* pins;				//Array of Pins the Pulser consistes of
		short numPins;				//The Number of Pins in the Array
		short center;				//The Center LED
		
		TimeKeeper *modeTimer;			//Timer for repeating the current step. (repeat constantly)
		TimeKeeper *stepTimer;			//Timer for Changing the step. (repeat at seprate interval)
		TimeKeeper *ledTimer;			//Timer for Changing the LED to turn on in the next step. (repeat constantly)
		
		void runMode();				//Links currentMode numbers to pattern functions
		
		void pulseCycle();			//Move the LEDs back and forth in a line
		void pulseForward();			//Move the LEDs forward in a line
		void pulseBackward();			//Move the LEDs backward in a line
		void starCycle();			//Move the LEDs to and fro from the center
		void starIn();				//Move the LEDs into the center from edges
		void starOut();				//Move the LEDs out-to the edges from the center
		void crissCross();			//Move the LEDs aross whole array.
		
		void ledChanger();			//Handles Cycling of LEDs when multipule are needed on at once.
		void stepChanger();			//Handles Cycling step of Mode at timed interval
		void light(short led);			//Handles Lighting a specified LED
};
#endif
/*
|| @changelog
|| | 1.2 2012-05-23 - Gus Michel : Added on and off
|| | 1.1 2012-05-21 - Gus Michel : crissCross pattern, simplified other patterns code for effiency
|| | 1.0 2012-05-20 - Gus Michel : Initial Release
|| #
*/
