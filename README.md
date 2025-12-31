# stm32-bootloader

Bootloader features

    Configurable application space
    Flash erase
    Flash programming
    Flash verification after programming
    Checksum verification
    Flash protection check, write protection enable/disable
    Extended error handling, fail-safe design
    Bootloader firmware update and the ability to perform full chip re-programming: enter ST's built-in bootloader from software (without triggering the BOOT pin)
    Serial tracing over SWO for easier debugging and development
    Easy to customize and port to other microcontrollers


To write a bootloader for the STM32F446RE, we'll write a two-part firmware:

1. Bootloader ( live at the start of Flash): This will decide what to do at reset (perhaps run app? stay in update mode?) jump to ST ROM bootloader

2. Application (lives at an offset): the "real" firmware

## Flash Layout

STM32F446RE has 512 KB flash. This flash is erased in sectors, and the first sectors are small (16 KB) then bigger (64 KB, 128 KB)

