# STM32 Bootloader

> For a higher-level project overview and visuals, see:  
> https://manushpatell.github.io/manush-portfolio/#/projects/stm32-bootloader

This repository contains a **custom flash-resident bootloader** for the **STM32F446RE** microcontroller.

The bootloader executes immediately after reset and serves as the system’s **first layer of control**, responsible for validating application firmware, enforcing memory safety, and safely transferring execution to the main application.

The design prioritizes **correct boot flow, fault containment, and low-level control**, while remaining modular and adaptable to other STM32 or Cortex-M devices.

---

## Bootloader Capabilities

- **Configurable application flash region**
- **Application integrity validation**
  - Initial stack pointer validation (SRAM bounds)
  - Reset handler validation (flash region, alignment, Thumb state)
- **Flash operation support**
  - Sector-aware erase logic
  - Boundary-checked flash programming
- **Boot-time fault containment**
  - Prevents execution of invalid or corrupted firmware
  - Safe fallback to bootloader mode
- **Modular architecture**
  - MCU-specific logic isolated from boot policy
  - Designed for extension with update protocols or checksums

---

## Architecture Overview

The firmware is divided into **two independent images**:

### Bootloader
- Resides at the **start of flash memory**
- Executes immediately after reset
- Responsibilities:
  - Validate application firmware structure
  - Enforce memory boundaries during flash operations
  - Coordinate execution flow (run application or remain in bootloader)
  - Prepare CPU state for safe handoff

### Application
- Resides at a **fixed offset in flash**
- Contains the main product firmware
- Assumes the bootloader has already validated system state and memory

This separation ensures that application updates cannot overwrite or corrupt the bootloader itself.

---

## Boot Process

At a high level, the boot process follows these steps:

1. **System reset**
2. CPU begins execution at the start of flash (bootloader)
3. Bootloader reads the application’s vector table from flash
4. Application validation checks are performed:
   - Initial stack pointer lies within SRAM bounds
   - Reset handler lies within the application flash region
   - Reset handler is correctly aligned and indicates Thumb state
   - Optional checksum framework hook
5. If the application is valid:
   - Interrupts are disabled
   - Vector table is relocated to the application
   - Main stack pointer (MSP) is reset
   - Execution jumps to the application reset handler
6. If validation fails:
   - Execution remains in the bootloader
   - Recovery or update actions may be taken

---

## Flash Layout (STM32F446RE)

The STM32F446RE contains **512 KB of internal flash**, organized into sectors of varying sizes.

Typical layout:

0x08000000 ── Bootloader (protected region)
0x0800XXXX ── Application start (configurable offset)
0x08080000 ── End of flash



### Flash Sector Organization

- Sectors 0–3: **16 KB each**
- Sector 4: **64 KB**
- Sectors 5–11: **128 KB each**

The bootloader is placed entirely within the early small sectors to allow:
- Fine-grained protection
- Safe application erasure and reprogramming
- Reduced risk during update operations

---

## Firmware Validation

Before transferring control to the application, the bootloader performs multiple safety checks:

- **Stack Pointer Validation**
  - Must lie within valid SRAM address range
  - Must meet alignment requirements
- **Reset Handler Validation**
  - Must lie within the application flash region
  - Must be correctly aligned
  - Must indicate Thumb execution state
- **Boundary Enforcement**
  - Prevents flash operations outside the application region

If any check fails, the application is not executed.

---

## System Bootloader (ROM) Support

The bootloader is **designed to support** jumping to ST’s built-in system bootloader directly from software, without toggling the BOOT pin.

This enables:
- Device recovery
- Use of ST-provided programming tools
- Full device reprogramming if required

---

## Portability

The bootloader is structured to allow reuse across different devices by modifying:
- Flash layout configuration
- Memory boundary definitions
- MCU-specific startup and flash control logic

This allows adaptation to other STM32 families or ARM Cortex-M microcontrollers.

---

## Project Scope & Status

This project focuses on:
- Correct boot flow
- Memory safety
- Cortex-M–level execution handoff mechanics

Flash update protocols, checksum algorithms, and communication interfaces are intentionally modular and may be extended depending on application requirements.

The emphasis is on **low-level understanding and system architecture**, rather than a fully packaged firmware update solution.

---

## Disclaimer

This bootloader is intended for educational and development purposes.  
Thorough validation and testing are recommended before deployment in production or safety-critical systems.
