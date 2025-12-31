/*
 * STM32F446_BOOT.ld
 *
 * Bootloader linker script.
 *
 * Defines:
 * - Flash origin and length reserved for bootloader
 * - SRAM usage for bootloader runtime
 *
 * This script enforces physical memory isolation.
 */


MEMORY
{
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 128K
  FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 512K
}

