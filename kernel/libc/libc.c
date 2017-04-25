#include <libc/libc.h>

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

uint32_t memset(void *dest, uint8_t val, size_t count) {
  uint8_t *dest_ptr = dest;
  for (uint32_t counter = 0; counter != count; counter++) {
    *dest_ptr = (unsigned char)val;
    dest_ptr++;
  }
  return 0;
}

char *itoa(int32_t value, char *str, uint32_t base) {  // code taken from OSDev wiki
  char *rc;
  char *ptr;
  char *low;
  // Check for supported base.
  if (base < 2 || base > 36) {
    *str = '\0';
    return str;
  }
  rc = ptr = str;
  // Set '-' for negative decimals.
  if (value < 0 && base == 10) {
    *ptr++ = '-';
  }
  // Remember where the numbers start.
  low = ptr;
  // The actual conversion.
  do {
    // Modulo is negative for negative value. This trick makes abs()
    // unnecessary.
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[35 + value % base];
    value /= base;
  } while (value);
  // Terminating the string.
  *ptr-- = '\0';
  // Invert the numbers.
  while (low < ptr) {
    char tmp = *low;
    *low++ = *ptr;
    *ptr-- = tmp;
  }
  return rc;
}

char *ltoa(int64_t value, char *str, uint32_t base) {  // code taken from OSDev wiki
  char *rc;
  char *ptr;
  char *low;
  // Check for supported base.
  if (base < 2 || base > 36) {
    *str = '\0';
    return str;
  }
  rc = ptr = str;
  // Set '-' for negative decimals.
  if (value < 0 && base == 10) {
    *ptr++ = '-';
  }
  // Remember where the numbers start.
  low = ptr;
  // The actual conversion.
  do {
    // Modulo is negative for negative value. This trick makes abs()
    // unnecessary.
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[35 + value % base];
    value /= base;
  } while (value);
  // Terminating the string.
  *ptr-- = '\0';
  // Invert the numbers.
  while (low < ptr) {
    char tmp = *low;
    *low++ = *ptr;
    *ptr-- = tmp;
  }
  return rc;
}
