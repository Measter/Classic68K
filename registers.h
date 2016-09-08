#ifndef REGISTERS_H
#define REGISTERS_H

#define X_BIT 4
#define N_BIT 3
#define Z_BIT 2
#define V_BIT 1
#define C_BIT 0

class Registers {
public:
	union {
		unsigned long data_arr[8];
		struct {
			unsigned long d0;
			unsigned long d1;
			unsigned long d2;
			unsigned long d3;
			unsigned long d4;
			unsigned long d5;
			unsigned long d6;
			unsigned long d7;
		} data;
	};
	union {
		unsigned long address_arr[8];
		struct {
			unsigned long a0;
			unsigned long a1;
			unsigned long a2;
			unsigned long a3;
			unsigned long a4;
			unsigned long a5;
			unsigned long a6;

			union {
				unsigned long a7;
				unsigned long stack;
			};
		} address;
	};
	unsigned long pc;
	union
	{
		struct
		{
			unsigned char status_flag;
			unsigned char status_system;
		};
		unsigned int status;
	};

	void init_registers();

	void dump_registers() const;
};

extern Registers registers;

#endif
