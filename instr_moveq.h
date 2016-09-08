#ifndef INSTR_MOVEQ_H
#define INST_MOVEQ_H

/////////////////////////
// 
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_moveq				0xF100
#define INSTR_MASK_moveq_VAL			0x7000

////////
// Source/Destination Masks/Shifts
////////

// Masks
#define INSTR_DEST_REGISTER_MASK_moveq		0xE00

// Shifts
#define INSTR_DEST_REG_SHIFT_moveq			0x9 

#endif // !INSTR_MOVEQ_H