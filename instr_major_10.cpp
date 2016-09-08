#include "InstructionExecution.h"
#include "InstructionMasks.h"
#include "registers.h"
#include "memory.h"

////////////////////////
// Major 10
////////////////////////

bool Core::instr_major_group_10(unsigned int instruction) {
	bool result;

	switch (instruction & GROUP_MINOR_MASK) {
		case GROUP_MINOR_00:
			result = instr_minor_group_1000(instruction);
			break;
		case GROUP_MINOR_01:
			result = instr_minor_group_1001(instruction);
			break;
		case GROUP_MINOR_10:
			result = instr_minor_group_1010(instruction);
			break;
		case GROUP_MINOR_11:
			result = instr_minor_group_1011(instruction);
			break;

		default:
			result = false;
			break;
	}

	return result;
}

bool Core::instr_minor_group_1000(unsigned int instruction) {
	return false;
}
bool Core::instr_minor_group_1001(unsigned int instruction) {
	return false;
}
bool Core::instr_minor_group_1010(unsigned int instruction) {
	return false;
}
bool Core::instr_minor_group_1011(unsigned int instruction) {
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