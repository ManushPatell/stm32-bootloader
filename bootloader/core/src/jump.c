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
#include "../Drivers/CMSIS/Include/core_cm4.h"

#define APP1_START()
#define APP2_START

void jump_to_application(uint32_t app_start_addr)
{
    /*
    When jumping applications, we expect a specific startup
    sequence
    1. Disable interrupts, preventing the bootloader from firing inside the app
    2. Stop Systick which is an iterrupt soure
    3. Change vector table offset (VTOR) to application start address. Now based off application vector table
    4. Set the stack pointer (MSP)
    5. Jump to Reset_handler
    */
    __disable_irq();

    /* Suspend SysTick Register */
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk);

    SCB->VTOR = app_start_addr;
    /*The stack is where the CPU stores: local vars, return addr, interrupt context
    App expects own stack, not the bootloaders*/

    uint32_t app_sp = *(uint32_t *)app_start_addr;
    __set_MSP(app_sp);

    /*Reset handler is second entry in vector table*/
    uint32_t app_reset = *(uint32_t *)(app_start_addr + 4);

    if ((app_reset & 0x1) == 0)
    {
        while (1)
            ;
    }

    ((void (*)(void))app_reset)();
}
