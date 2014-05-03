#include "interruptions.h"

int _interruptions_count=0;

Interruptions::Interruptions() {
	
}

void Interruptions::no() {
	_interruptions_count += 1;
	if (_interruptions_count == 1) {
		// noInterrupts();
		sei();
	}
}

void Interruptions::yes() {
	_interruptions_count -= 1;
	if (_interruptions_count == 0) {
		// interrupts();
		cli();
	}
}