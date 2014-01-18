/*
||
|| @file 	CharlieLed.cpp
|| @version	1.0
|| @author	Gus Michel
|| @contact	gus3@michelfamily.org
||
|| @description
|| | Provide an easy way to manage Charlieplexed LEDs.
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
#ifndef CHARLIELED_H
#define CHARLIELED_H

#include <WProgram.h>
#include "Arduino.h"

class CharlieLed {
	public:
		CharlieLed(short ivlt, short ignd);
		short getVoltagePin();			//Returns vlt
		short getGroundPin();			//Returns gnd
	private: 
		short vlt;				//LEDs Voltage Pin
		short gnd;				//LEDs Ground Pin
};
#endif
/*
|| @changelog
|| | 1.0 2012-05-20 - Gus Michel : Initial Release
|| #
*/
