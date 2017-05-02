#include <arch/i386/memory/multiboot.h>
#include <stdint.h>


#define KBD_DAT 0x60
#define KBD_STACMD 0x64

void clearscreen();
void initkbd();
void kin(char *kintext);
void panic(char* err);
void bootmsg(multiboot_info_t *mbd);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);
void haltcpu(void);
void brk(void);
void kout_mem(char *membase, char *sepchar, char *memlenght, char type);

