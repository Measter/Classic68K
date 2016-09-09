#include "InstructionExecution.h"
#include "InstructionMasks.h"
#include "registers.h"
#include "memory.h"

////////////////////////
// Major 00
////////////////////////

bool Core::instr_major_group_00(unsigned int instruction) {
	bool result;

	switch (instruction & GROUP_MINOR_MASK) {
		case GROUP_MINOR_00:
			return instr_minor_group_0000(instruction);
		default:
			return instr_minor_group_00_move(instruction);
	}
}

bool Core::instr_minor_group_0000(unsigned int instruction) {
	if( is_instr( instruction, andiccr ) ) {
		return instr_andiccr();
	}

	if( is_instr( instruction, eoriccr ) ) {
		return instr_eoriccr();
	}

	if( is_instr( instruction, oriccr ) ) {
		return instr_oriccr();
	}
	
	if (is_instr(instruction, movep)) {		// MoveP
		if (get_instr_size(instruction, movep) == size(movep, long))
			instr_movep<unsigned long>(instruction);
		else
			instr_movep<unsigned int>(instruction);

		return true;
	}

	return false;
}
bool Core::instr_minor_group_00_move(unsigned int instruction) {
	unsigned int mode, reg;
	
	if (is_instr(instruction, movea)) {		// MoveA
		switch (get_instr_size(instruction, movea)) {
			case size(movea, word):
				return instr_movea<unsigned int>(instruction);
			case size(movea, long):
				return instr_movea<unsigned long>(instruction);
			default:
				return false;
		}
	}

	if (is_instr(instruction, move)) {		// Move
		mode = get_instr_dest_mode(instruction, move) >> get_instr_dest_mode_shift(move);
		reg = get_instr_dest_register(instruction, move) >> get_instr_dest_reg_shift(move);

		if (mode == MODE_ADDR_DIR)
			return false;

		if (mode == MODE_OTHER && (reg != REG_ABS_LONG && reg != REG_ABS_WORD))
			return false;

		switch (get_instr_size(instruction, move)) {
			case size(move, byte):
				return instr_move<unsigned char>(instruction);
			case size(move, word):
				return instr_move<unsigned int>(instruction);
			case size(move, long):
				return instr_move<unsigned long>(instruction);
			default:
				return false;
		}
	}

	return false;
}

///////////
// Minor 00
///////////

bool Core::instr_andiccr() {
	unsigned int value;
	ram.get_memory(registers.pc, value);
	registers.pc += 2;

	registers.status_flag &= value & 0xFF;

	return true;
}

bool Core::instr_eoriccr() {
	unsigned int value;
	ram.get_memory(registers.pc, value);
	registers.pc += 2;

	registers.status_flag ^= value & 0xFF;

	return true;
}

bool Core::instr_oriccr() {
	unsigned int value;
	ram.get_memory(registers.pc, value);
	registers.pc += 2;

	registers.status_flag |= value & 0xFF;

	return true;
}




template<typename T>
bool Core::instr_movep(unsigned int instruction) {
	unsigned char dir = instruction & (1 << 7);
	unsigned char dataRegID = get_instr_dest_register(instruction, movep) >> get_instr_dest_reg_shift(movep);

	unsigned long address;
	ram.get_memory(registers.pc, address);
	registers.pc += 2;

	address >>= 16;
	address += registers.address_arr[get_instr_source_register(instruction, movep)];

	if (dir) {
		// Register to memory.
		unsigned char i;
		for (i = 0; i < sizeof(T) * 2; i += 2) {
			ram.set_memory(address, static_cast<unsigned char>(registers.data_arr[dataRegID] >> (3 - i / 2) * 8));
			address += 2;
		}
	}
	else {
		// Memory to register.
		registers.data_arr[dataRegID] = 0;
		unsigned char i, val;
		for (i = 0; i < sizeof(T) * 2; i += 2) {
			ram.get_memory(address, val);
			registers.data_arr[dataRegID] <<= 8;
			registers.data_arr[dataRegID] |= val;
			address += 2;
		}
	}

	return true;
}



///////////
// Minor --
///////////

template<typename T>
bool Core::instr_movea(unsigned int instruction)
{
	T value;
	bool result = get_from_effective_address(get_instr_source_mode(instruction, movea) >> get_instr_source_mode_shift(movea),
											 get_instr_source_register(instruction, movea),
											 instruction, value);

	if (!result) return false;

	registers.address_arr[get_instr_dest_register(instruction, movea) >> get_instr_dest_reg_shift(movea)] = sign_extend(value);

	return true;
}

template<typename T>
bool Core::instr_move(unsigned int instruction)
{
	T value;
	
	bool result = get_from_effective_address(get_instr_source_mode(instruction, move) >> get_instr_source_mode_shift(move),
											 get_instr_source_register(instruction, move),
											 instruction, value);

	if (!result) return false;

	result = set_from_effective_address<T>(get_instr_dest_mode(instruction, move) >> get_instr_dest_mode_shift(move),
										   get_instr_dest_register(instruction, move) >> get_instr_dest_reg_shift(move),
										   instruction, value);

	if (!result) return false;

	set_condition_code(Status::Leave,
					   is_negative(value) ? Status::Set : Status::Clear,
					   value == 0 ? Status::Set : Status::Clear,
					   Status::Clear,
					   Status::Clear);

	return true;
}