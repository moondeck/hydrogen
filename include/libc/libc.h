#include <stddef.h>
#include <stdint.h>

uint32_t memset(void *dest, uint8_t val, size_t count);
uint32_t memcpy(void *src, uint8_t *dest, size_t length);
char *itoa(int32_t value, char *str, uint32_t base);
char *ltoa(int64_t value, char *str, uint32_t base);
