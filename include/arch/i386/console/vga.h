#include <stdint.h>
#include <libc/libc.h>

void legacy_vga_clear(void);
void legacy_vga_newline(void);
void legacy_vga_print(uint8_t vga_character, uint8_t vga_color);