#ifndef INSTRUCTION_MASKS_H
#define INSTRUCTION_MASKS_H

#include "instr_move.h"
#include "instr_movea.h"
#include "instr_movetoccr.h"
#include "instr_movefromsr.h"
#include "instr_movem.h"
#include "instr_movep.h"
#include "instr_moveq.h"


/////////////////////////
// Group Codes
/////////////////////////

#define GROUP_MAJOR_MASK		0xC000
#define GROUP_MINOR_MASK		0x3000

#define GROUP_MAJOR_00			0x0000
#define GROUP_MAJOR_01			0x4000
#define GROUP_MAJOR_10			0x8000
#define GROUP_MAJOR_11			0xC000

#define GROUP_MINOR_00			0x0000
#define GROUP_MINOR_01			0x1000
#define GROUP_MINOR_10			0x2000
#define GROUP_MINOR_11			0x3000


/////////////////////////
// Effective Address Source/Destination Masks and Values
/////////////////////////

// Generic Modes
#define MODE_DATA_DIR			0x0
#define	MODE_ADDR_DIR			0x1
#define	MODE_ADDR_INDIR			0x2
#define	MODE_ADDR_INDIR_POST	0x3
#define	MODE_ADDR_INDIR_PRE		0x4
#define	MODE_ADDR_DISP			0x5
#define	MODE_ADDR_INDEX			0x6
#define	MODE_OTHER				0x7

// Generic Registers
#define REG_ABS_WORD			0x0
#define REG_ABS_LONG			0x1
#define REG_ABS_VALUE			0x4
#define REG_PC_DISP				0x2
#define REG_PC_INDEX			0x3




#define is_instr(instr, name)			(instr & INSTR_MASK_##name) == INSTR_MASK_##name##_VAL
#define get_instr_size(instr, name)		(instr & INSTR_SIZE_MASK_##name)
#define size(name, size)				INSTR_SIZE_##name##_##size

#define get_instr_dest_register(instr, name)	(instr & INSTR_DEST_REGISTER_MASK_##name)
#define get_instr_dest_mode(instr, name)		(instr & INSTR_DEST_MODE_MASK_##name)
#define get_instr_source_register(instr, name)	(instr & INSTR_SOURCE_REGISTER_MASK_##name)
#define get_instr_source_mode(instr, name)		(instr & INSTR_SOURCE_MODE_MASK_##name)

#define get_instr_source_mode_shift(name)		INSTR_SOURCE_MODE_SHIFT_##name
#define get_instr_dest_mode_shift(name)			INSTR_DEST_MODE_SHIFT_##name
#define get_instr_dest_reg_shift(name)			INSTR_DEST_REG_SHIFT_##name

#define get_mode_value(name, reg, type) INSTR_MODE_VAL_##name##_##reg##_##type
#define get_reg_value(name, reg, type) INSTR_REG_VAL_##name##_##reg##_##type

#endif