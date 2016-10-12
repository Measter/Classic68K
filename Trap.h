#ifndef TRAP_H
#define TRAP_H

#define TRAP_VECTOR_IO 15

#define TRAP_TASK_IO_TIME 8

class Trap
{
public:
	static bool IsValidVector(unsigned char vector);

	static void ExecuteTrap(unsigned char vector);
};

#endif