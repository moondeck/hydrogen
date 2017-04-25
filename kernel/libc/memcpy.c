#include <string.h>

uint32_t memcpy(void *src, uint8_t *dest, size_t length) {
  uint32_t count = 0;
  uint8_t *src_ptr = src;
  for (count = 0; count != length; count++) {
    *dest = *src_ptr;
    src_ptr++;
    dest++;
  }
  return 0;
}
