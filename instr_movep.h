#ifndef INSTR_MOVEP_H
#define INST_MOVEP_H

/////////////////////////
// 
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_movep				0xF138
#define INSTR_MASK_movep_VAL			0x0108

////////
// Size Masks
////////

#define INSTR_SIZE_MASK_movep		0x0040
#define INSTR_SIZE_movep_word		0x0000
#define INSTR_SIZE_movep_long		0x0040

////////
// Source/Destination Masks/Shifts
////////

// Masks
#define INSTR_DEST_REGISTER_MASK_movep			0xE00
#define INSTR_SOURCE_REGISTER_MASK_movep		0x007

// Shifts
#define INSTR_DEST_REG_SHIFT_movep			0x9 

#endif // !INSTR_MOVEP_H