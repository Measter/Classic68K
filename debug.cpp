#include "debug.h"
#include <Arduino.h>

const char digits[] = "0123456789ABCDEF";
char buffer[4];
unsigned char buffer_in_loc = 0;

void print_byte(unsigned char value, unsigned char newLine ){
	char str[3];
	str[2] = 0;

	str[0] = digits[value/16];
	str[1] = digits[value%16];

	if(newLine){
		Serial.println(str);
	} else {
		Serial.print(str);
	}
}

void print_word(unsigned int value, unsigned char newLine ){
	char str[5];
	str[4] = 0;

        int i;
	for( i = 3; i >= 0; i--) {
		str[i] = digits[value%16];
		value = value/16;
	}

	if(newLine){
		Serial.println(str);
	} else {
		Serial.print(str);
	}
}

void print_word_bin(unsigned int value, unsigned char newLine) {
	char str[17];
	str[16] = 0;

        int i;
	for( i = 15; i >= 0; i--) {
		str[i] = digits[value%2];
		value = value/2;
	}

	if(newLine){
		Serial.println(str);
	} else {
		Serial.print(str);
	}
}

void print_long(unsigned long value, unsigned char newLine ){
	char str[9];
	str[8] = 0;

        int i;
	for( i = 7; i >= 0; i--) {
		str[i] = digits[value%16];
		value = value/16;
	}

	if(newLine){
		Serial.println(str);
	} else {
		Serial.print(str);
	}
}

// Returns true if the buffer was filled.
// Call get_debug_input() to grab input and clear buffer.
bool update_debug_input() {
	if( Serial.available() ) {
		char input = Serial.read();

		if( !isHexadecimalDigit( input ) )
			return false;

		if( isDigit( input ) )
			buffer[buffer_in_loc] = input - '0';
		else {
			input = toLowerCase(input);
			buffer[buffer_in_loc] = input - 'a' + 10;
		}

		buffer_in_loc++;
		if (buffer_in_loc == 4) {
			buffer_in_loc = 0;
			return true;		// Filled buffer, so indicate so.
		}
	}

	return false;
}

unsigned int get_debug_input() {
	unsigned int value = 0;

	unsigned char i;
	for (i = 0; i < 4; i++) {
		value = (value << 4) + buffer[i];
	}

	return value;
}