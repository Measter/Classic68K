#ifndef INSTR_MASKS_MINOR_0110_H
#define INSTR_MASKS_MINOR_0110_H

/////////////////////////
// Minor Group 01 10 opcode masks and shifts.
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_bcc						0xF000
#define INSTR_MASK_bcc_VAL					0x6000

////////
// Size Masks
////////

////////
// Source/Destination Masks/Shifts
////////

// Masks
#define INSTR_SOURCE_MODE_MASK_bcc			0xF000

// Shifts
#define INSTR_SOURCE_MODE_SHIFT_bcc			0x8

#endif // !INSTR_MASKS_MINOR_0110_H