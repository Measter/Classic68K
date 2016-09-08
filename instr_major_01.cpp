#include "InstructionExecution.h"
#include "InstructionMasks.h"
#include "registers.h"
#include "memory.h"

////////////////////////
// Major 01
////////////////////////

bool Core::instr_major_group_01(unsigned int instruction) {
	bool result;

	switch (instruction & GROUP_MINOR_MASK) {
		case GROUP_MINOR_00:
			result = instr_minor_group_0100(instruction);
			break;
		case GROUP_MINOR_01:
			result = instr_minor_group_0101(instruction);
			break;
		case GROUP_MINOR_10:
			result = instr_minor_group_0110(instruction);
			break;
		case GROUP_MINOR_11:
			result = instr_minor_group_0111(instruction);
			break;

		default:
			result = false;
			break;
	}

	return result;
}

bool Core::instr_minor_group_0100(unsigned int instruction) {
	unsigned int mode, reg;

	if (is_instr(instruction, movefromsr))	// MoveFromSR
	{
		mode = get_instr_dest_mode(instruction, movefromsr) >> get_instr_dest_mode_shift(movefromsr);
		reg = get_instr_dest_register(instruction, movefromsr) >> get_instr_dest_reg_shift(movefromsr);

		if (mode == INSTR_MODE_VAL_move_addr_dir || (reg != REG_ABS_LONG && reg != REG_ABS_WORD))
			return false;

		return instr_movefromsr(instruction);
	}

	if (is_instr(instruction, movetoccr))	// MoveToCCR
	{
		if ((get_instr_source_mode(instruction, movetoccr) >> get_instr_source_mode_shift(movetoccr)) == INSTR_MODE_VAL_move_addr_dir)
			return false;

		return instr_movetoccr(instruction);
	}

	if (is_instr(instruction, movem)) {		// MoveM

		mode = get_instr_dest_mode(instruction, movem) >> get_instr_dest_mode_shift(movem);
		reg = get_instr_dest_register(instruction, movem) >> get_instr_dest_reg_shift(movem);

		if (mode == MODE_DATA_DIR || mode == MODE_ADDR_DIR || (mode == MODE_OTHER && reg == REG_ABS_VALUE))
			return false;

		unsigned int dir = get_instr_source_mode(instruction, movem);
		// Memory to register.
		if (dir && mode == MODE_ADDR_INDIR_PRE)
			return false;

		// Register to memory.
		if (!dir && (mode == MODE_ADDR_INDIR_POST || (mode == MODE_OTHER && (reg == REG_PC_DISP || reg == REG_PC_INDEX))))
			return false;

		if (get_instr_size(instruction, movem) == size(movem, word))
			return instr_movem<unsigned int>(instruction);
		else
			return instr_movem<unsigned long>(instruction);
	}

	return false;
}
bool Core::instr_minor_group_0101(unsigned int instruction) {
	return false;
}
bool Core::instr_minor_group_0110(unsigned int instruction) {
	return false;
}
bool Core::instr_minor_group_0111(unsigned int instruction) {
	if (is_instr(instruction, moveq)) 		// MoveQ
		return instr_moveq(instruction);

	return false;
}


///////////
// Minor 00
///////////

bool Core::instr_movefromsr(unsigned int instruction) {
	return set_from_effective_address<unsigned int>(get_instr_dest_mode(instruction, movefromsr) >> get_instr_dest_mode_shift(movefromsr),
													get_instr_dest_register(instruction, movefromsr),
													instruction, registers.status & 0xA71F);
}

bool Core::instr_movetoccr(unsigned int instruction) {
	unsigned int value;

	bool result = get_from_effective_address(get_instr_source_mode(instruction, movetoccr) >> get_instr_source_mode_shift(movetoccr),
											 get_instr_source_register(instruction, movetoccr),
											 instruction, value);

	if (!result) return false;

	registers.status = (registers.status & 0xFFE0) | (value & 0x1F);

	return true;
}

template<typename T>
bool Core::instr_movem(unsigned int instruction) {
	unsigned int direction = get_instr_source_mode(instruction, movem);
	unsigned char mode = get_instr_dest_mode(instruction, movem) >> get_instr_dest_mode_shift(movem);
	unsigned char reg = get_instr_dest_register(instruction, movem) >> get_instr_dest_reg_shift(movem);

	unsigned int reg_list, dispRegID;
	ram.get_memory(registers.pc, reg_list);
	registers.pc += 2;

	unsigned long address;

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
			}
			break;
		default:
			return false;
	}

	if (direction != 0) {
		// Memory to register.
		unsigned char i;
		T value;
		for (i = 0; i < 16; i++) {
			if (reg_list & 1 << i) {
				ram.get_memory(address, value);
				registers.data_arr[i] = sign_extend(value);
				address += sizeof(T);
			}
		}

		// Handle post-increment.
		if (mode == MODE_ADDR_INDIR_POST)
			registers.address_arr[reg] = address;
	}
	else {
		// Register to memory.

		// In pre-decrement, the register list is reversed, so we reverse it back here. WHY?!?
		unsigned char i;
		for (i = 0; i < 16; i++) {
			if (reg_list & 1 << i) {
				if (mode == MODE_ADDR_INDIR_PRE) {
					address -= sizeof(T);
					ram.set_memory(address, static_cast<T>(registers.data_arr[15 - i]));
				}

				if (mode != MODE_ADDR_INDIR_PRE) {
					ram.set_memory(address, static_cast<T>(registers.data_arr[i]));
					address += sizeof(T);
				}
			}
		}
	}

	return true;
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

bool Core::instr_moveq(unsigned int instruction) {
	unsigned char regID = get_instr_dest_register(instruction, moveq) >> get_instr_dest_reg_shift(moveq);
	unsigned char value = instruction;

	registers.data_arr[regID] = sign_extend(value);

	set_condition_code(Status::Leave,
					   is_negative(value) ? Status::Set : Status::Clear,
					   value == 0 ? Status::Set : Status::Clear,
					   Status::Clear,
					   Status::Clear);

	return true;
}