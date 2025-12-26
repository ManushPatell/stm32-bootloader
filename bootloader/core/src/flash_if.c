/*
 * flash_if.c
 *
 * Flash memory interface for STM32F4 Device
 *
 * Responsibilities:
 * - Erase application flash sectors
 * - Program flash words safely
 * - Enforce flash boundaries defined by platform configuration
 *
 * This file is MCU-family specific
 * No boot decision logic should exist here
 *
 * Flash behaviour differs between STM32 families, so if we change MCU, we only rewrite one file
 */
