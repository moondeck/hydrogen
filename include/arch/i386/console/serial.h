#include <arch/i386/io/io.h>

#define COM1 0x3F8
#define COMPORT COM1

void com_1_interrupt(void);
void init_serial();
char serial_io_wait();

uint8_t kout(char *koutstring);
uint8_t kout_char(char koutchar);