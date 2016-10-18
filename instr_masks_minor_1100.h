#ifndef INSTR_MASKS_MINOR_1100_H
#define INSTR_MASKS_MINOR_1100_H

/////////////////////////
// Minor Group 11 00 opcode masks and shifts.
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_and						0xF000
#define INSTR_MASK_and_VAL					0xC000

////////
// Size Masks
////////

#define INSTR_SIZE_MASK_and					0x00C0
#define INSTR_SIZE_and_byte					0x0000
#define INSTR_SIZE_and_word					0x0040
#define INSTR_SIZE_and_long					0x0080

////////
// Source/Destination Masks/Shifts
////////

// Masks

#define INSTR_DEST_REGISTER_MASK_and		0xE00
#define INSTR_DEST_MODE_MASK_and			0x100
#define INSTR_SOURCE_REGISTER_MASK_and		0x007
#define INSTR_SOURCE_MODE_MASK_and			0x038

// Shifts

#define INSTR_SOURCE_MODE_SHIFT_and			0x3
#define INSTR_SOURCE_REG_SHIFT_and			0x0
#define INSTR_DEST_REG_SHIFT_and			0x9

#endif // !INSTR_MASKS_MINOR_1100_H