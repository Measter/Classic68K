#include "debug.h"
#include <Arduino.h>

const char digits[] = "0123456789ABCDEF";

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
