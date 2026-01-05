// platform.c
#include "platform.h"
#include "stm32f446xx.h"

/*
 * Platform-level initialization
 * - minimal hardware setup
 * - safe to call early
 */
void platform_init(void)
{
    // Turn on power to GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configure pin PA5 as an output (LED pin)
    GPIOA->MODER &= ~(3U << (5 * 2));
    GPIOA->MODER |= (1U << (5 * 2));

    GPIOA->ODR ^= (1 << 5);   // toggle LED
    GPIOA->ODR &= ~(1U << 5); // LED OFF
}

void blink_error_led(void)
{
    while (1)
    {
        GPIOA->ODR ^= (1 << 5);
        for (volatile uint32_t i = 0; i < 500000; i++)
            ;
    }
}
