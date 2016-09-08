#ifndef INSTR_MOVEFROMSR_H
#define INST_MOVEFROMSR_H

/////////////////////////
// 
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_movefromsr				0xFFC0
#define INSTR_MASK_movefromsr_VAL			0x40C0

////////
// Source/Destination Masks/Shifts
////////

// Masks
#define INSTR_DEST_REGISTER_MASK_movefromsr		0x007
#define INSTR_DEST_MODE_MASK_movefromsr			0x038

// Shifts
#define INSTR_DEST_MODE_SHIFT_movefromsr		0x3
#define INSTR_DEST_REG_SHIFT_movefromsr			0x0

#endif // !INSTR_MOVEFROMSR_H
