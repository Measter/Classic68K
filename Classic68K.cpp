#include "InstructionExecution.h"
#include "registers.h"
#include "memory.h"
#include "pins.h"
#include "debug.h"
#include <Arduino.h>

void setup() {
	Serial.begin(9600);

	Serial.println("Arduino Classic68k Emulator.");

	Serial.print("Initializing...");
	Serial.print(" Pins...");

	Serial.print(" Memory...");	
	ram.zero_memory();

	Serial.println(" Registers...");
	registers.init_registers();
}

void loop() {
	pins.update_inputs();
	pins.update_leds();

	if( pins.is_debug_pressed() && update_debug_input() ) {
		ram.set_memory(registers.pc, get_debug_input());
		registers.pc += 2;
		return;
	}

	if( pins.is_reset_pc_pressed() )
	{
		registers.pc = pins.get_input();

		if (pins.is_debug_pressed() ) {
			Serial.print("PC set: ");
			print_long(registers.pc, true);
		}

		return;
	}
	
	if( pins.is_deposit_pressed() ) {
		ram.set_memory(registers.pc, pins.get_input() );
		registers.pc += 2;
		return;
	}

	if( pins.is_mem_dump_pressed() ) {
		registers.dump_registers();
		ram.dump_memory( pins.get_input(), 0x2F );
		return;
	}

	if ( pins.is_step_pressed())
	{
		core.execute_next_instruction();
		return;
	}
}
