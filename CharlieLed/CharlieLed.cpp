#include "CharlieLed.h"

CharlieLed::CharlieLed(short ivlt, short ignd) {
	vlt = ivlt;
	gnd = ignd;
}

short CharlieLed::getVoltagePin() {
	return vlt;
}

short CharlieLed::getGroundPin() {
	return gnd;
}
