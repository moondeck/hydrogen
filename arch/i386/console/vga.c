#include <arch/i386/console/vga.h>

struct screen_legacy_struct {
    uint8_t character;
    uint8_t color;
};

typedef struct screen_legacy_struct screen_t;
screen_t *screen = 0xb8000;

uint8_t x_pos = 0;
uint8_t y_pos = 0;

void legacy_vga_clear(void) {
    memset(0xb8000, 0, (80 * 25 * sizeof(struct screen_legacy_struct)));
    x_pos = 0;
    y_pos = 0;
}

void legacy_vga_newline(void) {
    x_pos = 0;
    y_pos++;
}

void legacy_vga_print(uint8_t vga_character, uint8_t vga_color) {
    screen[(y_pos * 80) + x_pos].character = vga_character;
    screen[(y_pos * 80) + x_pos].color = vga_color;
    x_pos++;

    if (x_pos == 80) {
        legacy_vga_newline();
        if (y_pos == 25) {
           legacy_vga_clear(); 
        }
    }
}