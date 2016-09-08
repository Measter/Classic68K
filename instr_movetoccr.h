#ifndef INSTR_MOVETOCCR_H
#define INST_MOVETOCCR_H

/////////////////////////
// 
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_movetoccr				0xFFC0
#define INSTR_MASK_movetoccr_VAL			0x44C0

////////
// Source/Destination Masks/Shifts
////////

// Masks
#define INSTR_SOURCE_REGISTER_MASK_movetoccr		0x007
#define INSTR_SOURCE_MODE_MASK_movetoccr			0x038

// Shifts
#define INSTR_SOURCE_MODE_SHIFT_movetoccr			0x3

#endif // !INSTR_MOVETOCCR_H
