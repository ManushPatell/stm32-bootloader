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
