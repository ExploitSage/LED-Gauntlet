/*
||
|| @file 	TimeKeeper.cpp
|| @version	1.1
|| @author	Gus Michel
|| @contact	gus3@michelfamily.org
||
|| @description
|| | Provide a way of timing and delaying a task while keeping the 
|| | action more flexable and not delaying a whole program
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
#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

#include <WProgram.h>

class TimeKeeper {
	public:
		TimeKeeper(unsigned long interval);
		void reset();					//Resets the interval
		void disable();					//Turns off TimeKeeper
		void enable();					//Turns on TimeKeeper
		bool check();					//Returns true if interval has passed
		void setInterval(unsigned long interval);	//Set Timing Interval
	
	private: 
		bool active;					//is the TimeKeeper Active
		unsigned long previous;				//Previous time the finished
		unsigned long currentInterval;			//Inverval for TimeKeeper
};
#endif
/*
|| @changelog
|| | 1.1 2012-05-22 - Gus Michel : added enable and disable
|| | 1.0 2012-05-20 - Gus Michel : Initial Release
|| #
*/
