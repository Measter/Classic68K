#include "registers.h"
#include "debug.h"
#include <Arduino.h>

Registers registers;

void Registers::init_registers() {
	data.d0 = data.d1 = 0;
	data.d2 = data.d3 = 0;
	data.d4 = data.d5 = 0;
	data.d6 = data.d7 = 0;

	address.a0 = address.a1 = 0;
	address.a2 = address.a3 = 0;
	address.a4 = address.a5 = 0;
	address.a6 = address.a7 = 0;

	pc = 0x0100; 
	status = 0x2000;
}

void Registers::dump_registers() const {
	Serial.println();
	Serial.println("Register Dump:");
	
	Serial.print("D0: ");
	print_long(data.d0, 0);
	Serial.print("  D1: ");
	print_long(data.d1, 0);
	Serial.print("  D2: ");
	print_long(data.d2, 0);
	Serial.print("  D3: ");
	print_long(data.d3, 1);
	
	Serial.print("D4: ");
	print_long(data.d4, 0);
	Serial.print("  D5: ");
	print_long(data.d5, 0);
	Serial.print("  D6: ");
	print_long(data.d6, 0);
	Serial.print("  D7: ");
	print_long(data.d7, 1);

	Serial.print("A0: ");
	print_long(address.a0, 0);
	Serial.print("  A1: ");
	print_long(address.a1, 0);
	Serial.print("  A2: ");
	print_long(address.a2, 0);
	Serial.print("  A3: ");
	print_long(address.a3, 1);
	
	Serial.print("A4: ");
	print_long(address.a4, 0);
	Serial.print("  A5: ");
	print_long(address.a5, 0);
	Serial.print("  A6: ");
	print_long(address.a6, 0);
	Serial.print("  SP: ");
	print_long(address.stack, 1);

	Serial.print("PC: ");
	print_long(pc, true);

	Serial.println("          T S  INT   XNZVC");
	Serial.print("  Status: ");
        print_word_bin(status, true);
}
