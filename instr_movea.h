#ifndef INSTR_MOVEA_H
#define INSTR_MOVEA_H

/////////////////////////
// Movea
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_movea			0xC1C0
#define INSTR_MASK_movea_VAL		0x0040

////////
// Size Masks
////////

#define INSTR_SIZE_MASK_movea		0x3000
#define INSTR_SIZE_movea_word		0x3000
#define INSTR_SIZE_movea_long		0x2000

////////
// Source/Destination Masks/Shifts
////////

#define INSTR_DEST_REGISTER_MASK_movea		0xE00
#define INSTR_SOURCE_REGISTER_MASK_movea	0x007
#define INSTR_SOURCE_MODE_MASK_movea		0x038

// Move Shifts
#define INSTR_SOURCE_MODE_SHIFT_movea		0x3
#define INSTR_DEST_REG_SHIFT_movea			0x9  

#endif // !INSTR_MOVEA_H