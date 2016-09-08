#ifndef INSTR_MOVE_H
#define INST_MOVE_H

/////////////////////////
// Move
/////////////////////////

////////
// OpCode Masks
////////

#define INSTR_MASK_move				0xC000
#define INSTR_MASK_move_VAL			0

////////
// Size Masks
////////

#define INSTR_SIZE_MASK_move		0x3000
#define INSTR_SIZE_move_byte		0x1000
#define INSTR_SIZE_move_word		0x3000
#define INSTR_SIZE_move_long		0x2000

////////
// Source/Destination Masks/Shifts
////////

// Masks
#define INSTR_DEST_REGISTER_MASK_move		0xE00
#define INSTR_DEST_MODE_MASK_move			0x1C0
#define INSTR_SOURCE_REGISTER_MASK_move		0x007
#define INSTR_SOURCE_MODE_MASK_move			0x038

// Shifts
#define INSTR_SOURCE_MODE_SHIFT_move		0x3
#define INSTR_DEST_MODE_SHIFT_move			0x6
#define INSTR_DEST_REG_SHIFT_move			0x9

// Mode/Register values
#define INSTR_MODE_VAL_move_data_dir		0x0
#define	INSTR_MODE_VAL_move_addr_dir		0x1
#define	INSTR_MODE_VAL_move_addr_indir		0x2
#define	INSTR_MODE_VAL_move_addr_indir_post	0x3
#define	INSTR_MODE_VAL_move_addr_indir_pre	0x4
#define	INSTR_MODE_VAL_move_addr_disp		0x5
#define	INSTR_MODE_VAL_move_addr_index		0x6
#define	INSTR_MODE_VAL_move_other_other		0x7

#define INSTR_REG_VAL_move_abs_indir_word	0x0
#define INSTR_REG_VAL_move_abs_indir_long	0x1
#define INSTR_REG_VAL_move_abs_value		0x4
#define INSTR_REG_VAL_move_pc_disp			0x2
#define INSTR_REG_VAL_move_pc_index			0x3  

#endif // !INSTR_MOVE_H
