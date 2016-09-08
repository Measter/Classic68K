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


///////////
// Minor 01
///////////


///////////
// Minor 10
///////////


///////////
// Minor 11
///////////