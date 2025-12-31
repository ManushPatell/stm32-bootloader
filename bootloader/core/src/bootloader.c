/*
 * bootloader.c
 * High-level bootloader state machine
 *
 * Responsibilities:
 * - Check whether a valid application exists in the flash
 * - Validate application size / checksum if enabled (CRC)
 * - Coordinate firmware update process
 * - Request jumps to applicatino or system memory
 *
 * It won't write flash directly, or perform CPU register manipulation
 *
 * MCU-independent logic lives here
 */

#include <stdint.h>
#include <stdbool.h>
#include "../inc/platform.h"

/*
An app is considered valid if jumping to its Reset_Handler does not crash the CPU
all the CRC, firmware headers, and versions are extra safety

*/

bool app_is_valid(uint32_t app_start)
{
    uint32_t stack_pointer = *(uint32_t *)app_start;
    uint32_t reset_handler = *(uint32_t *)(app_start + 4);

    if (stack_pointer < SRAM_BASE || stack_pointer > SRAM_END_ADDR)
    {
        return false;
    }

    if (reset_handler > FLASH_BASE || reset_handler < FLASH_END_ADDR)
    {
        return false;
    }

    return true;
}