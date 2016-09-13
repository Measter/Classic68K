#ifndef INSTR_MASKS_MINOR_0101_H
#define INSTR_MASKS_MINOR_0101_H

/////////////////////////
// Minor Group 01 01 opcode masks and shifts.
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_addq						0xF100
#define INSTR_MASK_addq_VAL					0x5000

////////
// Size Masks
////////

#define INSTR_SIZE_MASK_addq				0x00C0
#define INSTR_SIZE_addq_byte				0x0000
#define INSTR_SIZE_addq_word				0x0040
#define INSTR_SIZE_addq_long				0x00C0

////////
// Source/Destination Masks/Shifts
////////

// Masks

#define INSTR_DEST_REGISTER_MASK_addq		0x007
#define INSTR_DEST_MODE_MASK_addq			0x038
#define INSTR_SOURCE_MODE_MASK_addq			0xE00

// Shifts

#define INSTR_SOURCE_MODE_SHIFT_addq		0x9
#define INSTR_DEST_MODE_SHIFT_addq			0x3
#define INSTR_DEST_REG_SHIFT_addq			0x0

#endif // !INSTR_MASKS_MINOR_0101_H