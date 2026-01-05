// flash_if.h
#ifndef FLASH_IF_H
#define FLASH_IF_H

#include <stdint.h>

void flash_init(void);
void flash_erase_region(uint32_t start, uint32_t length);
void flash_write(uint32_t address, const uint8_t *data, uint32_t length);

#endif
