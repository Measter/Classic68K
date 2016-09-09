#ifndef INSTR_MASKS_MINOR_0100_H
#define INSTR_MASKS_MINOR_0100_H

/////////////////////////
// Minor Group 01 00 opcode masks and shifts.
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_movefromsr						0xFFC0
#define INSTR_MASK_movefromsr_VAL					0x40C0

#define INSTR_MASK_movetoccr						0xFFC0
#define INSTR_MASK_movetoccr_VAL					0x44C0

#define INSTR_MASK_jmp								0xFFC0
#define INSTR_MASK_jmp_VAL							0x4EC0

#define INSTR_MASK_movem							0xFB80
#define INSTR_MASK_movem_VAL						0x4880

////////
// Size Masks
////////

#define INSTR_SIZE_MASK_movem						0x0040
#define INSTR_SIZE_movem_word						0x0000
#define INSTR_SIZE_movem_long						0x0040

////////
// Source/Destination Masks/Shifts
////////

// Masks

#define INSTR_DEST_REGISTER_MASK_movefromsr			0x007
#define INSTR_DEST_MODE_MASK_movefromsr				0x038

#define INSTR_SOURCE_REGISTER_MASK_movetoccr		0x007
#define INSTR_SOURCE_MODE_MASK_movetoccr			0x038

#define INSTR_DEST_REGISTER_MASK_jmp				0x7
#define INSTR_DEST_MODE_MASK_jmp					0x38

#define INSTR_DEST_REGISTER_MASK_movem				0x7
#define INSTR_DEST_MODE_MASK_movem					0x38


// Shifts

#define INSTR_DEST_MODE_SHIFT_movefromsr			0x3
#define INSTR_DEST_REG_SHIFT_movefromsr				0x0

#define INSTR_SOURCE_MODE_SHIFT_movetoccr			0x3

#define INSTR_DEST_MODE_SHIFT_jmp					0x3
#define INSTR_DEST_REG_SHIFT_jmp					0x0

#define INSTR_DEST_MODE_SHIFT_movem					0x3
#define INSTR_DEST_REG_SHIFT_movem					0x0 
#define INSTR_SOURCE_MODE_MASK_movem				0x0400

#endif // !INSTR_MASKS_MINOR_0100_H