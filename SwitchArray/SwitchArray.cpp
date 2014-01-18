#include "SwitchArray.h"

SwitchArray::SwitchArray(short switchpins[], short numswitches) {
	switchPins = (short*) calloc(numswitches, sizeof(short));
	for(short i = 0; i < numswitches; i++) {
		switchPins[i] = switchpins[i];
		pinMode(switchPins[i], INPUT_PULLUP);
	}
	numSwitches = numswitches;
	switchNumber = 0;
}

int SwitchArray::readSwitch() {
	switchNumber = 0;
	for(short i = 0; i < numSwitches; i++) {
		if(digitalRead(switchPins[i]) == true) {
			switchNumber = switchNumber + (int) ceil(pow(2, i));
		}
	}
	return switchNumber;
}

