#ifndef PIN_SETUP_H
#define PIN_SETUP_H

class IO {
private:
	bool is_debug;
	bool is_higher_leds;

	bool is_reset_pc;
	bool reset_pc_last;
	unsigned long last_reset_pc_time;

	bool is_deposit;
	bool deposit_last;
	unsigned long last_deposit_time;

	bool is_memory_dump;
	bool memory_dump_last;
	unsigned long last_memory_dump_time;

	bool is_step;
	bool step_last;
	unsigned long last_step_time;

	unsigned int data_input;
	unsigned long last_mem_out;
	unsigned long last_data_out;

	static void update_button(bool* btn, bool* btn_last, unsigned long* btn_time, unsigned char pin);

public:
	IO();
	void update_inputs();
	void update_leds() const;

	void set_memory_leds(long value) const;
	void set_data_leds(long value);

	unsigned int get_input();

	bool is_debug_pressed() const;
	bool is_reset_pc_pressed() const;
	bool is_deposit_pressed() const;
	bool is_mem_dump_pressed() const;
	bool is_step_pressed() const;
};

extern IO pins;

#endif
