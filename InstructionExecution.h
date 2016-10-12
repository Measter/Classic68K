#ifndef INSTRUCTION_EXECUTION_H
#define INSTRUCTION_EXECUTION_H

#include "InstructionMasks.h"
#include "registers.h"
#include "memory.h"

enum class Status : unsigned char { Leave, Set, Clear };

class Core {
private:
	bool had_invalid_opcode;

	void invalid_op_code(unsigned int opcode);

	template<typename T>
	bool get_from_effective_address(unsigned char mode, unsigned char reg, unsigned int instruction, T &value);

	template<typename T>
	bool set_from_effective_address(unsigned char mode, unsigned char reg, unsigned int instruction, T value);

	void set_condition_code(Status x_val, Status n_val, Status z_val, Status v_val, Status c_val);

	bool is_negative(unsigned char val);
	bool is_negative(unsigned int val);
	bool is_negative(unsigned long val);

	unsigned long sign_extend(unsigned long val);
	unsigned long sign_extend(unsigned int val);
	unsigned long sign_extend(unsigned char val);

	unsigned char reverse(unsigned char b);

	bool condition_test(unsigned char condition);

	bool calculate_effective_address(unsigned char mode, unsigned char reg, unsigned long &address);


	////////////////////////
	// Major Group 00
	////////////////////////

	bool instr_major_group_00(unsigned int instruction);

	bool instr_minor_group_0000(unsigned int instruction);
	bool instr_minor_group_00_move(unsigned int instruction);

	///////////
	// Minor 00
	///////////

	bool instr_andiccr();
	bool instr_eoriccr();
	bool instr_oriccr();

	template<typename T>
	bool instr_cmpi(unsigned int instruction);

	template<typename T>
	bool instr_movep(unsigned int instruction);

	///////////
	// Minor --
	///////////

	template<typename T>
	bool instr_movea(unsigned int instruction);

	template<typename T>
	bool instr_move(unsigned int instruction);


	////////////////////////
	// Major Group 01
	////////////////////////

	bool instr_major_group_01(unsigned int instruction);

	bool instr_minor_group_0100(unsigned int instruction);
	bool instr_minor_group_0101(unsigned int instruction);
	bool instr_minor_group_0110(unsigned int instruction);
	bool instr_minor_group_0111(unsigned int instruction);

	///////////
	// Minor 00
	///////////

	bool instr_trap(unsigned int instruction);

	bool instr_movefromsr(unsigned int instruction);
	bool instr_movetoccr(unsigned int instruction);

	bool instr_jmp(unsigned int instruction);

	template<typename T>
	bool instr_movem(unsigned int instruction);

	bool instr_lea(unsigned int instruction);


	///////////
	// Minor 01
	///////////


	///////////
	// Minor 10
	///////////


	///////////
	// Minor 11
	///////////

	bool instr_moveq(unsigned int instruction);



	////////////////////////
	// Major Group 02
	////////////////////////

	bool instr_major_group_10(unsigned int instruction);

	bool instr_minor_group_1000(unsigned int instruction);
	bool instr_minor_group_1001(unsigned int instruction);
	bool instr_minor_group_1010(unsigned int instruction);
	bool instr_minor_group_1011(unsigned int instruction);

	///////////
	// Minor 00
	///////////

	///////////
	// Minor 01
	///////////

	template<typename T>
	bool instr_addq(unsigned int instruction);

	///////////
	// Minor 10
	///////////

	bool instr_bcc(unsigned int instruction);


	///////////
	// Minor 11
	///////////


	////////////////////////
	// Major Group 03
	////////////////////////

	bool instr_major_group_11(unsigned int instruction);

	bool instr_minor_group_1100(unsigned int instruction);
	bool instr_minor_group_1101(unsigned int instruction);
	bool instr_minor_group_1110(unsigned int instruction);
	bool instr_minor_group_1111(unsigned int instruction);

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


public:
	Core();
	void execute_next_instruction();

	bool get_had_invalid_opcode() const;
};

extern Core core;

template<typename T>
bool Core::get_from_effective_address(unsigned char mode, unsigned char reg, unsigned int instruction, T &value)
{
	unsigned char registerValue = reg;
	unsigned int displaceVal;
	unsigned int dispRegID;
	unsigned long absAddress;

	switch (mode) {
		case MODE_DATA_DIR:
			value = registers.data_arr[registerValue];
			break;
		case MODE_ADDR_DIR:
			value = registers.address_arr[registerValue];
			break;
		case MODE_ADDR_INDIR:
			ram.get_memory(registers.address_arr[registerValue], value);
			break;
		case MODE_ADDR_INDIR_POST:
			ram.get_memory(registers.address_arr[registerValue], value);
			if (registerValue == 7)
				registers.address_arr[registerValue] += 2;
			else
				registers.address_arr[registerValue]++;

			break;
		case MODE_ADDR_INDIR_PRE:
			if (registerValue == 7)
				registers.address_arr[registerValue] -= 2;
			else
				registers.address_arr[registerValue]--;

			ram.get_memory(registers.address_arr[registerValue], value);

			break;
		case MODE_ADDR_DISP:
			ram.get_memory(registers.pc, displaceVal);
			registers.pc += 2;

			ram.get_memory(registers.address_arr[registerValue] + displaceVal, value);

			break;
		case MODE_ADDR_INDEX:
			ram.get_memory(registers.pc++, dispRegID);
			dispRegID >>= 4;

			ram.get_memory(registers.pc++, displaceVal);

			ram.get_memory(registers.address_arr[registerValue] + registers.address_arr[dispRegID] + displaceVal, value);

			break;
		case MODE_OTHER:
			// Contains word and long absolute addresses, absolute values, and displaced PC.
			// In this case, the operation is stored in the register value.
			switch (registerValue)
			{
				case REG_ABS_WORD:
					ram.get_memory(registers.pc, absAddress);
					registers.pc += 2;
					ram.get_memory(absAddress >> 16, value);
					break;
				case REG_ABS_LONG:
					ram.get_memory(registers.pc, absAddress);
					registers.pc += 4;
					ram.get_memory(absAddress, value);
					break;
				case REG_ABS_VALUE:
					if (sizeof(T) == 1) {
						ram.get_memory(registers.pc, displaceVal);
						registers.pc += 2;
						value = displaceVal;
					}
					else {
						ram.get_memory(registers.pc, value);
						registers.pc += sizeof(T);
					}
					break;
				case REG_PC_DISP:
					ram.get_memory(registers.pc, displaceVal);
					ram.get_memory(registers.pc + displaceVal, value);

					registers.pc += 2;
					break;
				case REG_PC_INDEX:
					ram.get_memory(registers.pc, dispRegID);
					displaceVal = dispRegID & 0xFF;
					dispRegID >>= 12;
					ram.get_memory(registers.pc + displaceVal + registers.data_arr[dispRegID], value);

					registers.pc += 2;
					break;
				default:
					return false;
			}
			break;
		default:
			return false;
	}

	return true;
}


template<typename T>
bool Core::set_from_effective_address(unsigned char mode, unsigned char reg, unsigned int instruction, T value)
{
	unsigned int displaceVal;
	unsigned int dispRegID;
	unsigned long absAddress;

	switch (mode) {
		case MODE_DATA_DIR:
			registers.data_arr[reg] &= 0xFFFFFF00;
			registers.data_arr[reg] |= value;
			break;
		case MODE_ADDR_INDIR:
			ram.set_memory(registers.address_arr[reg], value);
			break;
		case MODE_ADDR_INDIR_POST:
			ram.set_memory(registers.address_arr[reg], value);
			if (reg == 7)
				registers.address_arr[reg] += 2;
			else
				registers.address_arr[reg]++;

			break;
		case MODE_ADDR_INDIR_PRE:
			if (reg == 7)
				registers.address_arr[reg] -= 2;
			else
				registers.address_arr[reg]--;

			ram.set_memory(registers.address_arr[reg], value);

			break;
		case MODE_ADDR_DISP:
			ram.get_memory(registers.pc, displaceVal);
			registers.pc += 2;

			ram.set_memory(registers.address_arr[reg] + displaceVal, value);

			break;
		case MODE_ADDR_INDEX:
			ram.get_memory(registers.pc, displaceVal);
			registers.pc += 2;
			dispRegID = displaceVal >> 12;
			displaceVal = sign_extend( displaceVal & 0xFF );

			ram.set_memory(registers.address_arr[reg] + registers.data_arr[dispRegID] + displaceVal, value);

			break;
		case MODE_OTHER:
			// Contains word and long absolute addresses, absolute values, and displaced PC.
			// In this case, the operation is stored in the register value.
			switch (reg)
			{
				case REG_ABS_WORD:
					ram.get_memory(registers.pc, absAddress);
					registers.pc += 2;
					// absAddress got read as a long, so we need to drop the lower 16 bits.
					ram.set_memory(absAddress >> 16, value);
					break;
				case REG_ABS_LONG:
					ram.get_memory(registers.pc, absAddress);
					registers.pc += 4;
					ram.set_memory(absAddress, value);
					break;
				default:
					return false;
			}
			break;
		default:
			return false;
	}

	return true;
}


#endif

