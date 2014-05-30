#include "interruptions.h"
#include <Arduino.h>

int _interruptions_count=0;

Interruptions::Interruptions() {
	
}

void Interruptions::no() {
	_interruptions_count += 1;
	if (_interruptions_count == 1) {
		noInterrupts();
		// Serial.println("Interruptions - No - Disabled");
	}
}

void Interruptions::yes() {
	_interruptions_count -= 1;
	if (_interruptions_count == 0) {
		interrupts();
		// cli();
		// Serial.println("Interruptions - Yes - Enabled");
	}
}