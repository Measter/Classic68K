#include "Trap.h"
#include "registers.h"
#include <Arduino.h>

bool Trap::IsValidVector( unsigned char vector ) {
	switch( vector ) {
		case 15:
			return true;
		default:
			return false;
	}
}

void Trap::ExecuteTrap(unsigned char vector) {
	unsigned long taskID = registers.data.d0;

	if( vector == TRAP_VECTOR_IO && taskID == TRAP_TASK_IO_TIME ) {
		registers.data.d1 = millis() / 100;
	}
}