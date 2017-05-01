#include <kmalloc/kmalloc.h>

#define FREE_MAGIC 0x05C00BEE //0scoobee - Free Block MAGIC
#define USED_MAGIC 0xD00BED00 //doobedoo - Used Block MAGIC

struct heapstruct {
    uint32_t MAGIC;
    uint32_t prev;
    uint32_t next;
};

struct entrinfo {
    uint32_t address;
    uint32_t endaddress;
    uint32_t length;
};

uint32_t kmalloc(uint32_t bytes) {


}