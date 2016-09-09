#ifndef INSTR_MASKS_MINOR_0111_H
#define INSTR_MASKS_MINOR_0111_H

/////////////////////////
// Minor Group 01 11 opcode masks and shifts.
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_moveq				0xF100
#define INSTR_MASK_moveq_VAL			0x7000

////////
// Size Masks
////////

////////
// Source/Destination Masks/Shifts
////////

// Masks

#define INSTR_DEST_REGISTER_MASK_moveq		0xE00

// Shifts

#define INSTR_DEST_REG_SHIFT_moveq			0x9 

#endif // !INSTR_MASKS_MINOR_0111_H