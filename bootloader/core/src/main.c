/*
 * main.c
 *
 * Bootloader entry point
 * Executes immediately after reset
 *
 * Responsibilities:
 * - Initialize minimal hardware required by the bootloader
 * - Decide boot path (application, firmware updates, or system memory)
 * - Never contains flash logic or jump logic directly
 *
 * This file will represent the bootloader's flow, not hardware details
 */
