#ifndef INSTR_MASKS_MINOR_00--_H
#define INSTR_MASKS_MINOR_00--_H

/////////////////////////
// Minor Group 00 -- opcode masks and shifts.
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_movea					0xC1C0
#define INSTR_MASK_movea_VAL				0x0040

#define INSTR_MASK_move						0xC000
#define INSTR_MASK_move_VAL					0

////////
// Size Masks
////////

#define INSTR_SIZE_MASK_movea				0x3000
#define INSTR_SIZE_movea_word				0x3000
#define INSTR_SIZE_movea_long				0x2000

#define INSTR_SIZE_MASK_move				0x3000
#define INSTR_SIZE_move_byte				0x1000
#define INSTR_SIZE_move_word				0x3000
#define INSTR_SIZE_move_long				0x2000

////////
// Source/Destination Masks/Shifts
////////

// Masks

#define INSTR_DEST_REGISTER_MASK_movea		0xE00
#define INSTR_SOURCE_REGISTER_MASK_movea	0x007
#define INSTR_SOURCE_MODE_MASK_movea		0x038

#define INSTR_DEST_REGISTER_MASK_move		0xE00
#define INSTR_DEST_MODE_MASK_move			0x1C0
#define INSTR_SOURCE_REGISTER_MASK_move		0x007
#define INSTR_SOURCE_MODE_MASK_move			0x038

// Shifts

#define INSTR_SOURCE_MODE_SHIFT_movea		0x3
#define INSTR_DEST_REG_SHIFT_movea			0x9 

#define INSTR_SOURCE_MODE_SHIFT_move		0x3
#define INSTR_DEST_MODE_SHIFT_move			0x6
#define INSTR_DEST_REG_SHIFT_move			0x9

#endif // !INSTR_MASKS_MINOR_0000_H