#include "InstructionExecution.h"
#include "InstructionMasks.h"
#include "registers.h"
#include "memory.h"
#include "debug.h"
#include "pins.h"
#include <Arduino.h>

Core core;

Core::Core() {
	had_invalid_opcode = false;
}

void Core::execute_next_instruction()
{
	bool result;
	unsigned int instruction;
	ram.get_memory(registers.pc, instruction);
	registers.pc += 2;

	switch( instruction & GROUP_MAJOR_MASK ) {
		case GROUP_MAJOR_00:
			result = instr_major_group_00(instruction);
			break;
		case GROUP_MAJOR_01:
			result = instr_major_group_01(instruction);
			break;
		case GROUP_MAJOR_10:
			result = instr_major_group_10(instruction);
			break;
		case GROUP_MAJOR_11:
			result = instr_major_group_11(instruction);
			break;

		default: 
			result = false;
		break;
	}

	if( result )
		return;

	invalid_op_code(instruction);
}

bool Core::get_had_invalid_opcode() const {
	return had_invalid_opcode;
}


void Core::invalid_op_code(unsigned int opcode)
{
	had_invalid_opcode = true;

	if ( pins.is_debug_pressed() ) {
		Serial.println("Program Crash:");

		Serial.print("Invalid opcode ");
		print_word(opcode, true);

		registers.dump_registers();
		ram.dump_memory(registers.pc - 1 & ~15, 47);
	}
}

void Core::set_condition_code(Status x_val, Status n_val, Status z_val, Status v_val, Status c_val)
{
	if (x_val == Status::Clear)
		bitClear(registers.status, X_BIT);
	else if (x_val == Status::Set)
		bitSet(registers.status, X_BIT);

	if (n_val == Status::Clear)
		bitClear(registers.status, N_BIT);
	else if (n_val == Status::Set)
		bitSet(registers.status, N_BIT);

	if (z_val == Status::Clear)
		bitClear(registers.status, Z_BIT);
	else if (z_val == Status::Set)
		bitSet(registers.status, Z_BIT);

	if (v_val == Status::Clear)
		bitClear(registers.status, V_BIT);
	else if (v_val == Status::Set)
		bitSet(registers.status, V_BIT);

	if (c_val == Status::Clear)
		bitClear(registers.status, C_BIT);
	else if (c_val == Status::Set)
		bitSet(registers.status, C_BIT);
}

bool Core::is_negative(unsigned char val)
{
	return val & 0x80;
}
bool Core::is_negative(unsigned int val)
{
	return val & 0x8000;
}
bool Core::is_negative(unsigned long val)
{
	return val & 0x8000000;
}

unsigned long Core::sign_extend(unsigned long val)
{
	return val;
}
unsigned long Core::sign_extend(unsigned int val)
{
	long signed_long = static_cast<int>(val);

	return static_cast<unsigned long>(signed_long);
}
unsigned long Core::sign_extend(unsigned char val) {
	long signed_long = static_cast<char>(val);
	return static_cast<unsigned long>(signed_long);
}

unsigned char Core::reverse(unsigned char b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

bool Core::condition_test(unsigned char condition) {
	switch (condition) {
		case CONDITION_TRUE:
			return true;
		case CONDITION_FALSE:
			return false;
		case CONDITION_HIGH:
			return !is_carry_set && !is_zero_set;
		case CONDITION_LOW_OR_SAME:
			return is_carry_set && is_zero_set;
		case CONDITION_CARRY_CLEAR:
			return !is_carry_set;
		case CONDITION_CARRY_SET:
			return is_carry_set;
		case CONDITION_NOT_EQUAL:
			return !is_zero_set;
		case CONDITION_EQUAL:
			return is_zero_set;
		case CONDITION_OVERFLOW_CLEAR:
			return !is_overflow_set;
		case CONDITION_OVERFLOW_SET:
			return is_overflow_set;
		case CONDITION_PLUS:
			return !is_negative_set;
		case CONDITION_MINUS:
			return is_negative_set;
		case CONDITION_GREATER_OR_EQUAL:
			return (is_negative_set && is_overflow_set) || (!is_negative_set && !is_overflow_set);
		case CONDITION_LESS_THAN:
			return (is_negative_set && !is_overflow_set) || (!is_negative_set && is_overflow_set);
		case CONDITION_GREATER_THAN:
			return (is_negative_set && is_overflow_set && !is_zero_set) || (!is_negative_set && !is_overflow_set && !is_zero_set);
		case CONDITION_LESS_OR_EQUAL:
			return (is_zero_set) || (is_negative_set && !is_overflow_set) || (!is_negative_set && is_overflow_set);

		default:
			return false;
	}
}

bool Core::calculate_effective_address(unsigned char mode, unsigned char reg, unsigned long &address) {
	unsigned int dispRegID;

	switch (mode) {
		case MODE_ADDR_INDIR_POST:
		case MODE_ADDR_INDIR_PRE:
		case MODE_ADDR_INDIR:
			address = registers.address_arr[reg];
			break;

		case MODE_ADDR_DISP:
			ram.get_memory(registers.pc, address);
			registers.pc += 2;
			address = registers.address_arr[reg] + address >> 16;
			break;

		case MODE_ADDR_INDEX:
			ram.get_memory(registers.pc, dispRegID);
			registers.pc += 2;

			address = dispRegID & 0xFF + registers.address_arr[reg];
			break;

		case MODE_OTHER:
			if (reg == REG_ABS_WORD) {
				ram.get_memory(registers.pc, address);
				registers.pc += 2;
				address >>= 16;
			}
			else if (reg == REG_ABS_LONG) {
				ram.get_memory(registers.pc, address);
				registers.pc += 4;
			}
			else if (reg == REG_PC_DISP) {
				ram.get_memory(registers.pc, address);
				address = registers.pc + (address >> 16);
				registers.pc += 2;
			}
			else if (reg == REG_PC_INDEX) {
				ram.get_memory(registers.pc, dispRegID);
				address = dispRegID & 0xFF; // Only lower byte is the offset.
				dispRegID >>= 12; // Upper half was the register ID.

				address += registers.pc + registers.data_arr[dispRegID];

				registers.pc += 2;
			} else if( reg == REG_ABS_VALUE )
				return false;
			break;
		default:
			return false;
	}

	return true;
}