#include "TimeKeeper.h"
#include "Arduino.h"


TimeKeeper::TimeKeeper(unsigned long interval){
	active = true;
	previous = 0;
	currentInterval = interval;
}

void TimeKeeper::reset(){
	previous = millis();
}

void TimeKeeper::disable(){
	active = false;
}

void TimeKeeper::enable(){
	active = true;
}

bool TimeKeeper::check(){
	if ( active && (millis()-previous >= currentInterval) ) {
		previous = millis();
		return true;
	} else {
  		return false;
  	}
}

void TimeKeeper::setInterval(unsigned long interval){
	currentInterval = interval;
}
