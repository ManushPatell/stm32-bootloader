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

#include "bootloader.h"
#include "platform.h"

int main(void)
{

    // Initialize hardware (clocks, GPIO for LED/button, UART, etc)
    platform_init();

    if (bootloader_should_enter())
    {
        // Enter bootloader mode - wait for firmware update

        bootloader_run();
    }

    if (is_primary_app_valid())
    {
        jump_to_application(PRIMARY_APP); // Run main app
    }

    if (is_secondary_app_valid())
    {
        copy_secondary_to_primary();
        jump_to_application(PRIMARY_APP);
    }

    // should never reach here
    while (1)
    {
        blink_error_led(); // somethings gone wrong
    }
}