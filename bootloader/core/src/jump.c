/*
 * jump.c
 *
 * Low-level execution transfer routines.
 *
 * Responsibilities:
 * - Disable interrupts
 * - Relocate vector table
 * - Set main stack pointer
 * - Jump to application reset handler or system memory
 *
 * This code should be minimal, deterministic, and HAL-independent
 */

#include <stdint.h>
#include <stdio.h>

#define APP1_START ()
#define APP2_START

void jump_to_app(uint32_t app_start_addr)
{
}