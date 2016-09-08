#ifndef MEMORY_H
#define MEMORY_H

#define mem_size 6144

class Memory {
private:
	unsigned char memory[mem_size];
	long last_memory_access;

	bool memory_address_check(unsigned long address);

public:
	bool has_memory_crash;

	Memory();

	void zero_memory();
	
	void set_memory(unsigned long address, unsigned char value);
	void set_memory(unsigned long address, unsigned int value);
	void set_memory(unsigned long address, unsigned long value);


	void get_memory(unsigned long address, unsigned char &value);
	void get_memory(unsigned long address, unsigned int &value);
	void get_memory(unsigned long address, unsigned long &value);


	unsigned long get_last_memory_address() const;

	void dump_memory(unsigned long address, unsigned char length);
};

extern Memory ram;

#endif
