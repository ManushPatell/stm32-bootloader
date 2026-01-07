# STM32 Bootloader (STM32F446RE)

This repository contains a **custom flash-resident bootloader** for the **STM32F446RE** microcontroller.  
The bootloader executes immediately after reset and acts as the system’s first layer of control, responsible for validating firmware, managing flash operations, and safely transferring execution to the main application.

The design prioritizes **reliability, fault tolerance, and low-level control**, while remaining extensible and portable to other STM32 or Cortex-M devices.

---

## Bootloader Features

- **Configurable application flash region**
- **Flash erase and programming routines**
- **Post-program flash verification**
- **Checksum-based firmware integrity validation**
- **Flash protection management**
  - Read/write protection checks
  - Enable/disable write protection as required
- **Fail-safe design with extended error handling**
- **Bootloader self-update support**
- **Software-controlled entry into ST’s built-in ROM bootloader**
  - Jump to the system bootloader without using the BOOT pin
- **Serial trace output over SWO**
  - Simplifies debugging and development
- **Designed for portability**
  - Easily adaptable to other STM32 families or Cortex-M MCUs

---

## Architecture Overview

The firmware is divided into **two independent images**:

### 1. Bootloader
- Resides at the **start of flash memory**
- Executes immediately after reset
- Responsibilities:
  - Validate application firmware
  - Perform flash erase/program operations
  - Enforce memory boundaries
  - Decide execution flow (run application, stay in bootloader, or enter ROM bootloader)

### 2. Application
- Resides at a **fixed offset in flash**
- Contains the main product firmware
- Assumes the bootloader has already validated system state and memory

This separation ensures that application updates cannot overwrite or corrupt the bootloader.

---

## Boot Process

At a high level, the boot process follows these steps:

1. **System reset**
2. CPU begins execution at the start of flash (bootloader)
3. Bootloader reads the application’s vector table from flash
4. Application integrity checks are performed:
   - Initial stack pointer validation (SRAM bounds)
   - Reset handler address validation (application flash region)
   - Checksum verification
5. If the application is valid:
   - Interrupts are disabled
   - System state is cleaned
   - Vector table is relocated
   - Main stack pointer is reset
   - Execution jumps to the application reset handler
6. If validation fails:
   - Execution remains in the bootloader
   - Update or recovery actions may be taken

---

## Flash Layout (STM32F446RE)

The STM32F446RE contains **512 KB of internal flash**, organized into sectors of varying sizes.

Typical flash layout:

0x08000000 ── Bootloader
(protected flash region)

0x0800XXXX ── Application start
(configurable offset)

0x08080000 ── End of flash (512 KB)


### Flash Sector Organization

- Sectors 0–3: **16 KB each**
- Sector 4: **64 KB**
- Sectors 5–11: **128 KB each**

The bootloader is placed entirely within the early small sectors to allow:
- Fine-grained protection
- Safe application erasure and reprogramming
- Reduced risk during updates

---

## Firmware Validation

Before transferring control to the application, the bootloader performs multiple safety checks:

- **Stack Pointer Validation**
  - Must lie within valid SRAM address range
- **Reset Handler Validation**
  - Must lie within the application flash region
  - Must be correctly aligned
- **Checksum Verification**
  - Detects corrupted or partially programmed firmware
- **Boundary Enforcement**
  - Prevents flash operations outside the application region

If any check fails, the application is not executed.

---

## Entering the ST ROM Bootloader

The bootloader supports jumping to **ST’s built-in system bootloader** directly from software, without toggling the BOOT pin.

This enables:
- Full device reprogramming
- Recovery from invalid firmware
- Use of ST-provided tools and protocols

---

## Debugging & Tracing

For development and debugging, the bootloader provides:

- **SWO-based serial trace output**
- Lightweight logging without consuming UART peripherals
- Visibility into boot decisions and error conditions

---

## Portability

The bootloader is designed to be easily adapted by modifying:

- Flash layout configuration
- Memory boundary definitions
- MCU-specific startup and flash control logic

This allows reuse across different STM32 families or other ARM Cortex-M devices.

---

## Disclaimer

This bootloader is intended for educational and development purposes.  
Thorough testing is recommended before deployment in safety-critical or production systems.

---



