#include <arch/i386/console/serial.h>

void init_serial() {
  outb(COMPORT + 1, 0x00);
  outb(COMPORT + 2, 0xC7);

  outb(COMPORT + 3, inb(COMPORT + 3) | 0b10000000); //sets DLAB

  outb(COMPORT + 0, 0x01);
  outb(COMPORT + 1, 0x00); //set the baud rate to 115200 (no division)

  outb(COMPORT + 3, inb(COMPORT + 3) & ~0b10000000); //disables DLAB

  outb(COMPORT + 2, 0x01);
  outb(COMPORT + 3, 0x03);
  outb(COMPORT + 4, 0x01);
}

char serial_io_wait() {
  while (!(inb(COMPORT + 5) & 0x20));
  return 1;
}

uint8_t vga_en = 1;

uint8_t kout_char(char koutchar) {  // outputs a character to serial
  if (vga_en == 1) {
    legacy_vga_print(koutchar, 0x0F);
    return 0;
  } else {
    serial_io_wait();
    outb(COM1, koutchar);
    return 0;
  }
}

uint8_t kout(char *koutstring) {  // outputs a string (char array) to serial

  while (*koutstring != 0) {

      if (*koutstring == '\n') {
        if(vga_en == 1) {
          legacy_vga_newline();
        } else {
          kout_char('\r');
          kout_char('\n');
        }
        *koutstring++;

      } else {
        kout_char(*koutstring);
        *koutstring++;
      }
  }
  return 0;
}
