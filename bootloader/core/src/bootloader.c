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