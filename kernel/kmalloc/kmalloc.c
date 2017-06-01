#include <kmalloc/kmalloc.h>

//DISABLED FOR NOW!
//DISABLED FOR NOW!
//DISABLED FOR NOW!
//DISABLED FOR NOW!
//DISABLED FOR NOW!

#define FREE_MAGIC 0x05C00BEE //0scoobee - Free Block MAGIC
#define USED_MAGIC 0xD00BED00 //doobedoo - Used Block MAGIC

#ifdef __i386__
    #define KMALLOC_START (0x1000000 - sizeof(struct heapstruct))
    #define KMALLOC_END 0xC0000000
#endif

struct heapstruct {
    uint32_t MAGIC;
    struct heapstruct *next;
    uint32_t length;
    uint32_t pad;
};

struct heapstruct *heap_start = KMALLOC_START;

typedef struct heapstruct heapstruct_t;


void malloc_init() {
    heap_start->MAGIC = FREE_MAGIC;
    heap_start->next = KMALLOC_START;
    heap_start->length = 4096;
}

uintptr_t malloc(uint32_t bytes) {
    heapstruct_t *current_header;
    heapstruct_t *prev_header;

    prev_header = current_header = heap_start;

    while(1) {
        if(current_header->MAGIC == FREE_MAGIC) { //excuse me, is this free?
            while(current_header->length < bytes) { //orly, is free? can i crash here?
                alloc_page(current_header + current_header->length);
                current_header->length += 4096;
            }

            current_header->MAGIC = USED_MAGIC; //this region is now used
            prev_header = current_header;   //set "prev"
            current_header->length = bytes;

            current_header = (current_header + bytes + sizeof(heapstruct_t)); //go to the end

            //create a new header at the end
            current_header->MAGIC = FREE_MAGIC;
            current_header->length = 0;
            current_header->next = prev_header->next;
            prev_header->next = current_header;

            kprintf("prev: %x len %x next %x\n",prev_header,prev_header->length ,prev_header->next);
            return (uintptr_t) (prev_header + sizeof(heapstruct_t));
        }else { //oh sorry, its not, lets go find some other place   
            prev_header = current_header = current_header->next;
        }
    }
}

uintptr_t calloc(uint32_t bytes) {
    uintptr_t zerobytes = malloc(bytes);
    memset((void *) zerobytes, 0, bytes);
    return zerobytes;
}

void free(uintptr_t freebytes) {
    //implement me!
    
}

