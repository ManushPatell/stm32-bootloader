// platform.c
#include "platform.h"
#include "stm32f4xx.h"

/*
 * Platform-level initialization
 * - minimal hardware setup
 * - safe to call early
 */
void platform_init(void)
{
    // Optional: enable GPIO clocks if you use LEDs / buttons
    // RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Optional: basic delay source
}
