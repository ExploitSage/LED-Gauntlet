#include "BatteryMeter.h"

BatteryMeter::BatteryMeter(
	CharlieLed LEDs[],
	short numleds,
	short PINs[],
	short numpins,
	short vltpin,
	double fullVolt,
	double minVolt
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
	
	voltagePin = vltpin;
	max = fullVolt;
	min = minVolt;
	
	stepTime = 1;
	stepTimer = new TimeKeeper(stepTime);
}

void BatteryMeter::update() {
	voltage=((double)analogRead(voltagePin)/100);
	if(voltage < min) {
		numLightsOn = 0;
	} else if(voltage > max){
		numLightsOn = numLeds;
	} else {
		numLightsOn = (short)numLeds*((double)(voltage-min) /max);
	}
	if(stepTimer->check() == true) {
		updateStep();
	}
	light(currentStep);
}
bool BatteryMeter::updateStep() {
	currentStep++;
	if(currentStep >= numLightsOn) {
		currentStep = 0;
	}
}
void BatteryMeter::light(short led) {
	for(short i = 0; i < numPins; i++) {
		pinMode(pins[i], INPUT);
	}
	for(short i = 0; i < numPins ; i++) {
		if(leds[led].getVoltagePin() == pins[i]) {
			pinMode(pins[i], OUTPUT);
			digitalWrite(pins[i], HIGH);
		} else if(leds[led].getGroundPin() == pins[i]) {
			pinMode(pins[i], OUTPUT);
			digitalWrite(pins[i], LOW);
		}
	}
}
void BatteryMeter::off() {
	for(short i = 0; i < numPins; i++) {
		pinMode(pins[i], INPUT);
	}
}
