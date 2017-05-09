#include <kmalloc/kmalloc.h>

//DISABLED FOR NOW!
//DISABLED FOR NOW!
//DISABLED FOR NOW!
//DISABLED FOR NOW!
//DISABLED FOR NOW!

/*#define FREE_MAGIC 0x05C00BEE //0scoobee - Free Block MAGIC
#define USED_MAGIC 0xD00BED00 //doobedoo - Used Block MAGIC

#define kmalloc_start_addr 0x1000000
#define kmalloc_end_addr 0xC0000000

struct heapstruct {
    uint32_t MAGIC;
    uint32_t prev;
    uint32_t next;
    uint32_t length;
};

struct heapstruct *heap_curr;

void heap_entry(void *pointer, uint32_t magic, uint32_t next, uint32_t prev, uint32_t length) {
    heap_curr = (struct heapstruct*) pointer;
    heap_curr->prev = prev;
    heap_curr->next = next;
    heap_curr->MAGIC = magic;
}

void kmalloc_init() {
    heap_entry(kmalloc_start_addr, FREE_MAGIC, kmalloc_end_addr - sizeof(struct heapstruct), kmalloc_start_addr, kmalloc_end_addr - kmalloc_start_addr - sizeof(struct heapstruct));
    heap_entry(kmalloc_end_addr - sizeof(struct heapstruct), USED_MAGIC, kmalloc_start_addr, kmalloc_start_addr, 0);
    
}

uint32_t kmalloc(uint32_t bytes) {
    struct heapstruct_temp;
    uint32_t next_temp;
    uint32_t prev_addr_temp;

    heap_curr = kmalloc_start_addr;
    kprintf("KMALLOC CALLED!\n");
    kprintf("memory header at %x\nprev: %x next: %x length: %x\n",(uint32_t) heap_curr, heap_curr->prev, heap_curr->next, heap_curr->length);

    if(heap_curr->MAGIC == FREE_MAGIC && heap_curr->length >= bytes + (sizeof(struct heapstruct)*2)) {
        return (uint32_t) (heap_curr + sizeof(struct heapstruct));

    } else {
        kprintf("going to the next entry at %x\n", heap_curr->next);
        heap_curr = heap_curr->next;
        if(heap_curr->next = kmalloc_start_addr) panic("kmalloc just shit itself");
    }
}*/