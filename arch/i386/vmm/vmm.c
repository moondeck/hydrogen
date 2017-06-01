#include <arch/i386/vmm/vmm.h>
#include <arch/i386/memory/memory.h>
#include <libc/kprintf.h>

#define PDIR_PHYS 0x600000
#define PDIR_VIRT 0xFFFFF000

#define PSTRUCTURE_VIRT 0xFFC00000
static uint32_t *page_dir = (uint32_t *) PDIR_PHYS;
static uint32_t * const page_tab = (uint32_t*)0xFFC00000;



uint32_t get_virt_mapoffset(uint32_t PDIR_index) {
    return PSTRUCTURE_VIRT + (PDIR_index * 0x1000);
}

uint32_t map_pv(uint32_t virt, uint32_t phys, uint8_t flags) {
    uint32_t pd_index = (virt >> 22);
    uint32_t pt_index = (virt >> 12 );
    


    if(page_dir[pd_index]) {                        //is the entry there?
        *page_tab = get_virt_mapoffset(pd_index);   //if yes, just map it
    } else {                                        //if its not, do:
        page_dir[pd_index] = alloc_pframe();
        page_dir[pd_index] |= 3;
        *page_tab = get_virt_mapoffset(pd_index);
        memset((uint8_t *) get_virt_mapoffset(pd_index), 0, PAGE_SIZE);
    }

    page_tab[pt_index] = (phys & 0xFFFFF000) | (flags << 1) | 1;    //flags shifted by 1, since 

    load_cr3((uint32_t) PDIR_PHYS);
    return 0;
}

uint32_t unmap_pv(uint32_t virt) {
    uint32_t pd_index = (virt >> 22);
    uint32_t pt_index = (virt >> 12);

    dealloc_pframe(page_tab[pt_index] & 0xFFFFF000);
    page_tab[pt_index] = 0; //un-present
    invlpg(virt);   //invalidate tlb
    load_cr3((uint32_t) PDIR_PHYS);

    return 0;
}

void init_paging(void) {
    kprintf("current dir physical:%x virtual:%x\n", (uint32_t) PDIR_PHYS, (uint32_t) PDIR_VIRT);
    page_dir[1023] = PDIR_PHYS | 3;
    load_cr3((uint32_t) PDIR_PHYS);
    page_dir = (uint32_t *) PDIR_VIRT;
    uint32_t kernel_ro_section_end = (uint32_t) &data_end;
    for(uint32_t kernel_area_variable = 0x100000; kernel_area_variable < kernel_ro_section_end; kernel_area_variable += 4096){
        map_pv(kernel_area_variable, kernel_area_variable, 0);
    }
}

inline void invlpg(uint32_t addr) {
   asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}

uint32_t alloc_page(uint32_t alloc_addr) {
    map_pv(alloc_addr, alloc_pframe(), PFLAG_READWR);
    return 0;
}