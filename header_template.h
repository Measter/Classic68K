#ifndef INSTR_$OP$_H
#define INST_$OP$_H

/////////////////////////
// 
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_$op$				0xC000
#define INSTR_MASK_$op$_VAL			0x0

////////
// Size Masks
////////

#define INSTR_SIZE_MASK_$op$		0x3000
#define INSTR_SIZE_$op$_byte		0x1000
#define INSTR_SIZE_$op$_word		0x3000
#define INSTR_SIZE_$op$_long		0x2000

////////
// Source/Destination Masks/Shifts
////////

// Masks
#define INSTR_DEST_REGISTER_MASK_$op$		0xE00
#define INSTR_DEST_MODE_MASK_$op$			0x1C0
#define INSTR_SOURCE_REGISTER_MASK_$op$		0x007
#define INSTR_SOURCE_MODE_MASK_$op$			0x038

// Shifts
#define INSTR_SOURCE_MODE_SHIFT_$op$		0x3
#define INSTR_DEST_MODE_SHIFT_$op$			0x6
#define INSTR_DEST_REG_SHIFT_$op$			0x9 

#endif // !INSTR_$OP$_H
