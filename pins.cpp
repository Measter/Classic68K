#include "pins.h"
#include "memory.h"
#include <Arduino.h>

IO pins;

#define bit0 22
#define bit1 24
#define bit2 26
#define bit3 28
#define bit4 30
#define bit5 32
#define bit6 34
#define bit7 36

#define RESET_PC_PIN 5
#define DEPOSIT_PIN 4
#define STEP_PIN 3
#define MEMORY_DUMP_PIN 2

#define INPUT_INDICATOR_PIN 8

#define MEMORY_LED_DATA 10
#define MEMORY_LED_LATCH 11
#define MEMORY_LED_CLOCK 12

#define DEBOUNCE_TIME 10 // Time in ms.

// Needs to read from switches.
IO::IO() {
	is_debug = true;		// Hardcoded for now. Will have physical switch later.
	is_higher_leds = false;

	is_reset_pc = false;
	reset_pc_last = false;
	last_reset_pc_time = 0;

	is_deposit = false;
	deposit_last = false;
	last_deposit_time = 0;

	is_memory_dump = false;
	memory_dump_last = false;
	last_memory_dump_time = 0;

	is_step = false;
	step_last = false;
	last_step_time = 0;

	data_input = 0;
	last_mem_out = 0;
	last_data_out = 0;

	int i;
	for (i = bit0; i <= bit7; i += 2) {
		pinMode(i, INPUT_PULLUP);
	}

	// Shut off pin 13 LED
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);

	pinMode(MEMORY_LED_DATA, OUTPUT);
	pinMode(MEMORY_LED_CLOCK, OUTPUT);
	pinMode(MEMORY_LED_LATCH, OUTPUT);

	pinMode(RESET_PC_PIN, INPUT_PULLUP);
	pinMode(DEPOSIT_PIN, INPUT_PULLUP);
	pinMode(MEMORY_DUMP_PIN, INPUT_PULLUP);
	pinMode(STEP_PIN, INPUT_PULLUP);
}

void IO::update_inputs() {
	update_button(&is_reset_pc, &reset_pc_last, &last_reset_pc_time, RESET_PC_PIN);
	update_button(&is_deposit, &deposit_last, &last_deposit_time, DEPOSIT_PIN);
	update_button(&is_memory_dump, &memory_dump_last, &last_memory_dump_time, MEMORY_DUMP_PIN);
	update_button(&is_step, &step_last, &last_step_time, STEP_PIN);
}

void IO::update_leds() const {
	if( ram.get_last_memory_address() == last_mem_out )
		return;

	set_memory_leds(ram.get_last_memory_address());
}


inline void IO::update_button(bool* is_btn, bool* btn_last, unsigned long* btn_time, unsigned char pin) {
	bool curPressed = !digitalRead( pin );

	*btn_last = *is_btn;

	if (!curPressed && *is_btn) {
		*btn_time = millis();
		*is_btn = curPressed;
	}
	else if (curPressed && !*is_btn && millis() - *btn_time >= DEBOUNCE_TIME) {
		*is_btn = curPressed;
	}
}

unsigned int IO::get_input()
{
	// Wait for the user to release the button.
	while (is_deposit) {
		update_inputs();
		// Save some cycles while waiting.
		delay(50);
	}
	update_inputs();

	unsigned int value = 0;

	// Get high byte.
	int i;
	for (i = bit7; i >= bit0; i -= 2) {
		value = (value << 1) | !digitalRead(i);
	}

	digitalWrite(INPUT_INDICATOR_PIN, HIGH);
	while ( !is_deposit_pressed() ) {
		update_inputs();
		// Save some cycles while waiting.
		delay(50);
	}

	// Get low byte
	for (i = bit7; i >= bit0; i -= 2) {
		value = (value << 1) | !digitalRead(i);
	}

	digitalWrite(INPUT_INDICATOR_PIN, LOW);

	return value;
}

void IO::set_memory_leds(long value) const {

	if (is_higher_leds) {
		value >>= 16;
	}

	digitalWrite(MEMORY_LED_LATCH, LOW);
	digitalWrite(MEMORY_LED_CLOCK, LOW);
	shiftOut(MEMORY_LED_DATA, MEMORY_LED_CLOCK, MSBFIRST, value >> 8);
	shiftOut(MEMORY_LED_DATA, MEMORY_LED_CLOCK, MSBFIRST, value);
	digitalWrite(MEMORY_LED_LATCH, HIGH);
}

void IO::set_data_leds(long value) {

}


bool IO::is_debug_pressed() const {
	return is_debug;
}

bool IO::is_reset_pc_pressed() const {
	return is_reset_pc && !reset_pc_last;
}

bool IO::is_deposit_pressed() const {
	return is_deposit && !deposit_last;
}

bool IO::is_mem_dump_pressed() const {
	return is_memory_dump && !memory_dump_last;
}

bool IO::is_step_pressed() const {
	return is_step && !step_last;
}

