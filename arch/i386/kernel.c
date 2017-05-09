#include <arch/i386/kernel.h>

/*
 * this is the main kernel loop, not much happening here.
 */

extern int get_hileaf();
extern uint32_t _IRQ_TICK;

void kmain(multiboot_info_t *mbd_ptr) {

  legacy_vga_clear();
  gdt_install();
  remap_PIC(0x20, 0x28);
  idt_install();

  initkbd();
  init_serial();

  bootmsg(mbd_ptr);

  memory_init(mbd_ptr);

  pfa_init();
  
  init_paging();

  while (1) {
    kprintf("irq ticks: %d\n", _IRQ_TICK);
    brk();
  }

}
