#include "CharliePulser.h"

CharliePulser::CharliePulser(
	CharlieLed LEDs[],
	short numleds,
	short PINs[],
	short numpins,
	short mode,
	unsigned long time
    ) {
   	leds = (CharlieLed*) calloc(numleds, sizeof(CharlieLed));
	for(short i = 0; i < numleds; i++) {
		leds[i] = LEDs[i];
	}
	numLeds = numleds;
	
	pins = (short*) calloc(numpins, sizeof(short));
	for(short i = 0; i < numpins; i++) {
		pins[i] = PINs[i];
	}
	numPins = numpins;
	
	center = (short) (ceil((double)numLeds/2));
	
	ledTime = (unsigned long) 1;
	modeTime = (unsigned long) 1;
	stepTime = (unsigned long) time;
	
	currentStep = 1;
	currentLed = 0;
	currentMode = mode;
	
	ledTimer = new TimeKeeper(ledTime);
	modeTimer = new TimeKeeper(modeTime);
	stepTimer = new TimeKeeper(stepTime);
}

void CharliePulser::checkTimers() {
	if(modeTimer->check()) {
		runMode();
//		off();
//		pulseForward();
//		pulseBackward();
//		pulseCycle();
//		starIn();
//		starOut();
//		starCycle();
//		crissCross();
		if(ledTimer->check()) {
			ledChanger();
		}
	}
	if(stepTimer->check()) {
		stepChanger();
	}
}

void CharliePulser::ledChanger() {
	currentLed++;
	if(currentLed > 1) {
		currentLed = 0;
	}
}

void CharliePulser::stepChanger() {
	currentStep++;
	if(currentStep > numLeds*2) {
		currentStep = 1;
	}
}

void CharliePulser::light(short led) {
	for(short i = 0; i < numPins; i++) {
		pinMode(pins[i], INPUT);
	}
	for(short i = 0; i < numPins; i++) {
		if(leds[led].getVoltagePin() == pins[i]) {
			pinMode(pins[i], OUTPUT);
			digitalWrite(pins[i], HIGH);
		} else if(leds[led].getGroundPin() == pins[i]) {
			pinMode(pins[i], OUTPUT);
			digitalWrite(pins[i], LOW);
		}
	}
}

void CharliePulser::setTime(int time) {
	stepTimer->setInterval(time);
}

void CharliePulser::setMode(short mode) {
	currentMode = mode;
	currentStep = 1;
}

void CharliePulser::runMode() {
	switch(currentMode) {
			case 0:
				off();
				break;
			case 1:
				pulseForward();
				break;
			case 2:
				pulseBackward();
				break;
			case 3:
				pulseCycle();
				break;
			case 4:
				starIn();
				break;
			case 5:
				starOut();
				break;
			case 6:
				starCycle();
				break;
			case 7:
				crissCross();
				break;
			case 8:
				on();
				break;
		}
}




//PULSING PATTERNS
void CharliePulser::off() {
	for(short i = 0; i < numPins; i++) {
		pinMode(pins[i], INPUT);
	}
}

void CharliePulser::on() {
	for(int i = 0; i < numLeds; i++) {
		light(i);
		delay(1);
	}
}

void CharliePulser::pulseForward() {
	if(currentStep <= numLeds) {
		light((short) currentStep-1);
	} else {
		light((short) (currentStep-numLeds)-1);
	}
}

void CharliePulser::pulseBackward() {
	if(currentStep <= numLeds) {
		light((short) (numLeds-currentStep));
	} else {
		light((short) (numLeds-(currentStep-numLeds)));
	}
}

void CharliePulser::pulseCycle() {
	if(currentStep <= numLeds) {
		pulseForward();
	} else {
		pulseBackward();
	}
}

void CharliePulser::starCycle() {
	if(currentLed == 0) {
		pulseForward();
	} else {
		pulseBackward();
	}
}

void CharliePulser::starIn() {
	if(currentStep > center) {
		currentStep = 1;
	}
	starCycle();
}

void CharliePulser::starOut() {
	if(currentStep < center || currentStep > center*2) {
		currentStep = center;
	}
	starCycle();
}

void CharliePulser::crissCross() {
	if(currentStep*2 == numLeds) {
		currentStep++;
	}
	if((currentStep-numLeds)*2 == numLeds) {
		currentStep++;
	}
	starCycle();
}
