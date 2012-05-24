/*
||
|| @file 	Gauntlet2_0.ino
|| @version	2.6
|| @author	Gus Michel
|| @contact	gus3@michelfamily.org
||
|| @description
|| | Pulsing Led Gauntlet Sketch.
|| | 
|| | Requires the Following Libraries:
|| | CharlieLed
|| | TimeKeeper
|| | SwitchArray
|| | BatteryMeter
|| | CharliePulser
|| | These are all avalible at: https://github.com/gixxy
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
#include <CharliePulser.h>
#include <CharlieLed.h>
#include <TimeKeeper.h>
#include <SwitchArray.h>
#include <BatteryMeter.h>

unsigned long timer = 60;
short numPulsers = 4;
short numleds = 12;
short numpins = 4;
short startMode = 0; //OFF - TO BE USED
short numSwitches = 5;

short leftGreenPins[4] = {22, 24, 26, 28};
short leftBluePins[4] = {23, 25, 27, 29};
short rightGreenPins[4] = {30, 32, 34, 36};
short rightBluePins[4] = {31, 33, 35, 37};

CharlieLed leftGreenLeds[12] = {
  CharlieLed(22, 24),
  CharlieLed(24, 22),
  CharlieLed(24, 26),
  CharlieLed(26, 24),
  CharlieLed(26, 28),
  CharlieLed(28, 26),
  CharlieLed(22, 26),
  CharlieLed(26, 22),
  CharlieLed(24, 28),
  CharlieLed(28, 24),
  CharlieLed(22, 28),
  CharlieLed(28, 22)
};
CharlieLed leftBlueLeds[12] = {
  CharlieLed(23, 25),
  CharlieLed(25, 23),
  CharlieLed(25, 27),
  CharlieLed(27, 25),
  CharlieLed(27, 29),
  CharlieLed(29, 27),
  CharlieLed(23, 27),
  CharlieLed(27, 23),
  CharlieLed(25, 29),
  CharlieLed(29, 25),
  CharlieLed(23, 29),
  CharlieLed(29, 23)
};
CharlieLed rightGreenLeds[12] = {
  CharlieLed(30, 32),
  CharlieLed(32, 30),
  CharlieLed(32, 34),
  CharlieLed(34, 32),
  CharlieLed(34, 36),
  CharlieLed(36, 34),
  CharlieLed(30, 34),
  CharlieLed(34, 30),
  CharlieLed(32, 36),
  CharlieLed(36, 32),
  CharlieLed(32, 36),
  CharlieLed(36, 32)
 };
CharlieLed rightBlueLeds[12] = {
  CharlieLed(31, 33),
  CharlieLed(33, 31),
  CharlieLed(33, 35),
  CharlieLed(35, 33),
  CharlieLed(35, 37),
  CharlieLed(37, 35),
  CharlieLed(31, 35),
  CharlieLed(35, 31),
  CharlieLed(33, 37),
  CharlieLed(37, 33),
  CharlieLed(31, 37),
  CharlieLed(37, 31)
 };

CharliePulser *pulsers[4];

short switchPins[5] = {42, 43, 44, 45, 46};

SwitchArray* modeSwitches;

boolean previous = false;
boolean current = false;

short buttonPin = 47;

short potPin = 1;

int debounceInterval = 200;
long debounceTimer;

short batteryPins[4] = {38, 39, 40, 41};
short numBatteryPins = 4;
short numBatteryLeds = 12;
CharlieLed batteryLeds[12] = {
  CharlieLed(38, 39),
  CharlieLed(39, 38),
  CharlieLed(39, 40),
  CharlieLed(40, 39),
  CharlieLed(40, 41),
  CharlieLed(41, 40),
  CharlieLed(38, 40),
  CharlieLed(40, 38),
  CharlieLed(39, 41),
  CharlieLed(41, 39),
  CharlieLed(38, 41),
  CharlieLed(41, 38)
 };
 
short voltagePin = 0;
BatteryMeter *batteryMeter;
double maxVoltage = 7;
double minVoltage = 4;

void setup() {
  pulsers[0] = new CharliePulser(
    leftGreenLeds,
    numleds,
    leftGreenPins,
    numpins,
    startMode,
    timer
  );
  pulsers[1] = new CharliePulser(
    leftBlueLeds,
    numleds,
    leftBluePins,
    numpins,
    startMode,
    timer
  );
  pulsers[2] = new CharliePulser(
    rightGreenLeds,
    numleds,
    rightGreenPins,
    numpins,
    startMode,
    timer
  );
  pulsers[3] = new CharliePulser(
    rightBlueLeds,
    numleds,
    rightBluePins,
    numpins,
    startMode,
    timer
  );

  modeSwitches = new SwitchArray(
    switchPins, 
    numSwitches
  );
  batteryMeter = new BatteryMeter(
    batteryLeds,
    numBatteryLeds,
    batteryPins,
    numBatteryPins,
    voltagePin,
    maxVoltage,
    minVoltage
  );
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  
  free(leftGreenPins);
  free(leftBluePins);
  free(rightGreenPins);
  free(rightBluePins);
  free(leftGreenLeds);
  free(leftBlueLeds);
  free(rightGreenLeds);
  free(rightBlueLeds);
  free(switchPins);
  free(batteryLeds);
  free(batteryPins);
  
  debounceTimer = millis();
  
  readyBlink();
  
}

void loop() {
  batteryMeter->update();
  if(checkButton() == true) {
    reprogram();
  } else {
    for(int i = 0; i < numPulsers; i++) {
      pulsers[i]->setTime(scalePot(analogRead(potPin)));
      pulsers[i]->checkTimers();
    }
  }
}

boolean checkButton() {
  current = digitalRead(buttonPin);
  if(previous == false && current == true && millis() - debounceTimer > debounceInterval) {
    previous = current;
    return true;
  }
  previous = current;
  return false;
}

void reprogram() {
  for(int i = 0;i <numPulsers; i++) {
    pulsers[i]->off();
  }
  batteryMeter->off();
  
 for(int i = 0; i < numPulsers;) {
   pulsers[i]->on();
    if(checkButton() == true) {
      pulsers[i]->setMode(modeSwitches->readSwitch());
      pulsers[i]->off();
      i++;
    }
  }
}

int scalePot(int input) {
  return ((int)200*((double)input /1023));
}

void readyBlink() {
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, INPUT);
  pinMode(28, INPUT);
  digitalWrite(24, LOW);
  delay(450);
  for(int i = 0; i < 10; i++) {
      digitalWrite(22, HIGH);
      delay(50);
      digitalWrite(22, LOW);
      delay(50);
  }
  
}
