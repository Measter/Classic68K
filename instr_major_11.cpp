#include "InstructionExecution.h"
#include "InstructionMasks.h"
#include "registers.h"
#include "memory.h"

////////////////////////
// Major 11
////////////////////////

bool Core::instr_major_group_11(unsigned int instruction) {
	bool result;

	switch (instruction & GROUP_MINOR_MASK) {
		case GROUP_MINOR_00:
			result = instr_minor_group_1100(instruction);
			break;
		case GROUP_MINOR_01:
			result = instr_minor_group_1101(instruction);
			break;
		case GROUP_MINOR_10:
			result = instr_minor_group_1110(instruction);
			break;
		case GROUP_MINOR_11:
			result = instr_minor_group_1111(instruction);
			break;

		default:
			result = false;
			break;
	}

	return result;
}

bool Core::instr_minor_group_1100(unsigned int instruction) {
	unsigned int mode, reg, opMode;
	
	if (is_instr(instruction, and)) {
		opMode = get_instr_dest_mode(instruction, and);
		mode = get_instr_source_mode(instruction, and) >> get_instr_source_mode_shift(and);
		reg = get_instr_source_register(instruction, and) >> get_instr_source_reg_shift(and);

		// Effective address is source
		if( opMode == 0 && mode == MODE_ADDR_DIR ) {
			return false;
		}
		
		// Effective address is destination.
		if( opMode != 0 && (mode == MODE_ADDR_DIR || mode == MODE_DATA_DIR
			|| (mode == MODE_OTHER && (reg == REG_ABS_VALUE || reg == REG_PC_DISP || reg == REG_PC_INDEX)))) { 
			return false;
		}

		switch (get_instr_size(instruction, and)) {
			case size(and, byte):
				return instr_and<unsigned char>(instruction);
			case size(and, word):
				return instr_and<unsigned int>(instruction);
			case size(and, long):
				return instr_and<unsigned long>(instruction);
			default:
				return false;
		}
	}

	return false;
}
bool Core::instr_minor_group_1101(unsigned int instruction) {
	return false;
}
bool Core::instr_minor_group_1110(unsigned int instruction) {
	return false;
}
bool Core::instr_minor_group_1111(unsigned int instruction) {
	return false;
}


///////////
// Minor 00
///////////

template<typename T>
bool Core::instr_and(unsigned int instruction) {
	T opA, opB;
	unsigned long regVal;
	unsigned char registerID = get_instr_dest_register(instruction, and) >> get_instr_dest_reg_shift(and);
	bool result;

	regVal = registers.data_arr[registerID];
	opA = regVal;
	
	result = get_from_effective_address(get_instr_source_mode(instruction, and) >> get_instr_source_mode_shift(and),
										get_instr_source_register(instruction, and) >> get_instr_source_reg_shift(and),
										instruction, opB);

	if( !result ) return result;

	opA &= opB;

	// Non-zero is send to memory.
	if( get_instr_dest_mode( instruction, and ) ) {
		result = set_from_effective_address(get_instr_source_mode(instruction, and) >> get_instr_source_mode_shift(and),
											get_instr_source_register(instruction, and) >> get_instr_source_reg_shift(and),
											instruction, opB);
	} else {
		regVal &= !(static_cast<unsigned long>(static_cast<T>(-1)));
		regVal |= opA;
		registers.data_arr[registerID] = regVal;

		result = true;
	}

	set_condition_code(Status::Leave,
					   is_negative(opA) ? Status::Set : Status::Clear,
					   opA == 0 ? Status::Set : Status::Clear,
					   Status::Clear,
					   Status::Clear);
	
	return result;
}


///////////
// Minor 01
///////////


///////////
// Minor 10
///////////


///////////
// Minor 11
///////////