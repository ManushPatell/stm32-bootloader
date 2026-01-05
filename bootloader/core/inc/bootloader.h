#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdint.h>
#include <stdbool.h>

/* Bootloader decision logic */
bool bootloader_should_enter(void);
void bootloader_run(void);

/* Application validation */
bool app_is_valid(uint32_t app_start_addr);

/* Recovery */
void copy_secondary_to_primary(void);

#endif /* BOOTLOADER_H */
