#ifndef DEBUG_H
#define DEBUG_H

void print_byte(unsigned char value, unsigned char newLine );
void print_word(unsigned int value, unsigned char newLine );
void print_word_bin(unsigned int value, unsigned char newLine);
void print_long(unsigned long value,  unsigned char newLine );

bool update_debug_input();
unsigned int get_debug_input();
	
#endif
