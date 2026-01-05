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
#include "jump.h"

int main(void)
{

    // Initialize hardware (clocks, GPIO for LED/button, UART, etc)
    platform_init();

    if (bootloader_should_enter())
    {
        // Enter bootloader mode - wait for firmware update

        bootloader_run();
    }

    if (app_is_valid(PRIMARY_APP_START_ADDR))
    {
        jump_to_application(PRIMARY_APP_START_ADDR); // Run main app
    }

    if (app_is_valid(SECONDARY_APP_START_ADDR))
    {
        copy_secondary_to_primary();
        jump_to_application(SECONDARY_APP_START_ADDR);
    }

    // should never reach here
    while (1)
    {
        blink_error_led(); // somethings gone wrong
    }
}