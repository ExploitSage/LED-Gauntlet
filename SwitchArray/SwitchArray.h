/*
||
|| @file 	SwitchArray.cpp
|| @version	1.0
|| @author	Gus Michel
|| @contact	gus3@michelfamily.org
||
|| @description
|| | Use an array of switches(read as an 'n' bit number) to get a decimal answer
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
#ifndef SWITCHARRAY_H
#define SWITCHARRAY_H

#include <math.h>
#include "Arduino.h"

class SwitchArray {
	public:
		SwitchArray(short switchpins[], short numswitches);
		int readSwitch();			//Return the value of the Switches (read as bits)
	private:
		short numSwitches;			//Number of Switches in the Array
		short* switchPins;			//Pins that the Switches are plugged into
		int switchNumber;			//Value of the Switches (read as bits)
};
#endif
/*
|| @changelog
|| | 1.0 2012-05-20 - Gus Michel : Initial Release
|| #
*/
