#ifndef INSTR_MASKS_MINOR_0000_H
#define INSTR_MASKS_MINOR_0000_H

/////////////////////////
// Minor Group 00 00 opcode masks and shifts.
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_movep						0xF138
#define INSTR_MASK_movep_VAL					0x0108

#define INSTR_MASK_andiccr						0xFFFF
#define INSTR_MASK_andiccr_VAL					0x023C

#define INSTR_MASK_eoriccr						0xFFFF
#define INSTR_MASK_eoriccr_VAL					0x0A3C

#define INSTR_MASK_oriccr						0xFFFF
#define INSTR_MASK_oriccr_VAL					0x003C

////////
// Size Masks
////////

#define INSTR_SIZE_MASK_movep					0x0040
#define INSTR_SIZE_movep_word					0x0000
#define INSTR_SIZE_movep_long					0x0040

////////
// Source/Destination Masks/Shifts
////////

// Masks
#define INSTR_DEST_REGISTER_MASK_movep			0xE00
#define INSTR_SOURCE_REGISTER_MASK_movep		0x007

// Shifts
#define INSTR_DEST_REG_SHIFT_movep				0x9 

#endif // !INSTR_MASKS_MINOR_0000_H