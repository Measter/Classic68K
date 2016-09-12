#include "memory.h"
#include "pins.h"
#include "registers.h"
#include "debug.h"

#include <Arduino.h>

Memory ram;

Memory::Memory() {
	last_memory_access = 0;
	has_memory_crash = false;
}

void Memory::zero_memory() {
	long i;
	for (i = 0; i <= mem_max; i++) {
		memory[i] = 0;
	}
}

bool Memory::memory_address_check(unsigned long address)
{
	if (address % 2 == 0)
		return true;

	if (pins.is_debug_pressed()) {
		Serial.println("Program Crash:");

		Serial.print("Invalid Address ");
		print_long(address, true);

		registers.dump_registers();
		dump_memory(registers.pc - 1 & ~15, 47);
	}

	pins.set_memory_leds(0xFFFFF2);
	pins.set_data_leds(0xFFFFFFFF);
	has_memory_crash = true;

	return false;
}

void Memory::set_memory(unsigned long address, unsigned char value) {
	if (pins.is_debug_pressed()) {
		Serial.print("Mem set byte: ");
		print_long(address, false);
		Serial.print(": ");
		print_byte(value, true);
	}

	if (last_memory_access != address)
		last_memory_access = address;

	memory[address & mem_max] = value;
}

void Memory::set_memory(unsigned long address, unsigned int value) {
	if (pins.is_debug_pressed()) {
		Serial.print("Mem set word: ");
		print_long(address, false);
		Serial.print(": ");
		print_word(value, true);
	}

	if (!memory_address_check(address)) return;

	if (last_memory_access != address)
		last_memory_access = address;

	memory[address & mem_max] = value >> 8;
	memory[(address + 1) & mem_max] = value;
}

void Memory::set_memory(unsigned long address, unsigned long value) {
	if (pins.is_debug_pressed()) {
		Serial.print("Mem set long: ");
		print_long(address, false);
		Serial.print(": ");
		print_long(value, true);
	}

	if (!memory_address_check(address)) return;

	if (last_memory_access != address)
		last_memory_access = address;

	memory[address & mem_max] = value >> 24;
	memory[(address + 1) & mem_max] = value >> 16;
	memory[(address + 2) & mem_max] = value >> 8;
	memory[(address + 3) & mem_max] = value;
}


void Memory::get_memory(unsigned long address, unsigned char &value) {
	if (pins.is_debug_pressed()) {
		Serial.print("Mem get byte: ");
		print_long(address, false);
	}

	if (last_memory_access != address)
		last_memory_access = address;

	value = memory[address];

	if (pins.is_debug_pressed())
	{
		Serial.print(": ");
		print_byte(value, true);
	}
}

void Memory::get_memory(unsigned long address, unsigned int &value)
{
	if (pins.is_debug_pressed()) {
		Serial.print("Mem get word: ");
		print_long(address, false);
	}

	if (!memory_address_check(address)) return;

	if (last_memory_access != address)
		last_memory_access = address;

	value = memory[address] << 8;
	value |= memory[address + 1];

	if (pins.is_debug_pressed())
	{
		Serial.print(": ");
		print_word(value, true);
	}
}

void Memory::get_memory(unsigned long address, unsigned long &value)
{
	if (pins.is_debug_pressed()) {
		Serial.print("Mem get long: ");
		print_long(address, false);
	}
	
	if (!memory_address_check(address)) return;

	if (last_memory_access != address)
		last_memory_access = address;

	value = memory[address];
	value <<= 8;

	value |= memory[address+1];
	value <<= 8;

	value |= memory[address+2];
	value <<= 8;
	value |= memory[address+3];

	if (pins.is_debug_pressed())
	{
		Serial.print(": ");
		print_long(value, true);
	}
}


unsigned long Memory::get_last_memory_address() const {
	return last_memory_access;
}



void Memory::dump_memory(unsigned long address, unsigned char length) {
	Serial.println();
	Serial.println("Memory Dump:");

	Serial.print("          ");
	unsigned char j;
	unsigned char addrLen = min(length, 16);
	for (j = 0; j < addrLen; j++) {
		print_byte(j, false);
		Serial.print(" ");
	}

	Serial.println();
	print_long(address, false);
	Serial.print(": ");

	long i;
	j = 0;
	for (i = address; i <= address + length; i++, j++) {
		if (j == 16) {
			j = 0;
			Serial.println();
			print_long(i, false);
			Serial.print(": ");
		}

		print_byte(memory[i & mem_max], false);
		Serial.print(" ");
	}

	Serial.println();
}
