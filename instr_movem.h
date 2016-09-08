#ifndef INSTR_MOVEM_H
#define INST_MOVEM_H

/////////////////////////
// 
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_movem				0xFB80
#define INSTR_MASK_movem_VAL			0x4880

////////
// Size Masks
////////

#define INSTR_SIZE_MASK_movem		0x0040
#define INSTR_SIZE_movem_word		0x0000
#define INSTR_SIZE_movem_long		0x0040

////////
// Source/Destination Masks/Shifts
////////

// Masks
#define INSTR_DEST_REGISTER_MASK_movem		0x7
#define INSTR_DEST_MODE_MASK_movem			0x38

// Shifts
#define INSTR_DEST_MODE_SHIFT_movem			0x3
#define INSTR_DEST_REG_SHIFT_movem			0x0 

#define INSTR_SOURCE_MODE_MASK_movem		0x0400

#endif // !INSTR_MOVEM_H
