// Centralizes all addresses and sizes
/*
 * platform.h
 *
 * Centralized platform configuration
 *
 * Responsibilities:
 * - Define flash layout (bootloader/app boundaries)
 * - Define memory base addresses (SRAM, flash, system memory)
 * - Act as the single source of truth for address for address calculations
 *
 * No code should hardcode memory addresses outside this file


┌─────────────────────────────────────┐
│  0x08000000                         │
│  ┌───────────────────────────────┐  │
│  │   BOOTLOADER (32KB)           │  │ ← Always runs first on power-up
│  │   - The "manager"             │  │
│  │   - Decides what to do        │  │
│  └───────────────────────────────┘  │
│  0x08008000                         │
│  ┌───────────────────────────────┐  │
│  │   PRIMARY APP (224KB)         │  │ ← Your main firmware
│  │   - Your actual program       │  │
│  │   - Blink LED, read sensors   │  │
│  │   - Do useful work            │  │
│  │                               │  │
│  │   [HEADER - last 72 bytes]    │  │ ← Metadata about the firmware
│  └───────────────────────────────┘  │
│  0x08040000                         │
│  ┌───────────────────────────────┐  │
│  │   SECONDARY/BACKUP APP        │  │ ← Emergency backup
│  │   (224KB)                     │  │
│  │                               │  │
│  │   [HEADER - last 72 bytes]    │  │
│  └───────────────────────────────┘  │
│  0x08078000                         │
└─────────────────────────────────────┘

Power On → CPU jumps to 0x08000000 → Bootloader main() executes

An application imagine is compiled firmware that's ready to run

The three scenarios:

Scenario 1: Normal boot (most common)
Power On -> Bootlaoder runs -> Checks primary app -> Valid! -> Jump to primary -> your app runs

Scenario 2: Firmware Update
Power On → Bootloader runs → Button pressed (or UART command)
→ Enter update mode → Receive new firmware over UART
→ Write to primary app space → Verify it's good
→ Reboot → Jump to new app

Scenario 3: Recovery (Update Failed)
Power On → Bootloader runs → Primary app corrupted!
→ Check secondary → Secondary valid!
→ Copy secondary to primary → Jump to app


[POWER ON / RESET]
                │
                ▼
    ┌───────────────────────┐
    │   BOOTLOADER RUNS     │ ← 0x08000000
    │   (Always first!)     │
    └───────────┬───────────┘
                │
                ▼
       ┌────────────────┐
       │ Button pressed?│
       │ Update command?│
       └───┬────────┬───┘
           │        │
       YES │        │ NO
           │        │
           ▼        ▼
    ┌──────────┐  ┌─────────────────┐
    │ FIRMWARE │  │ Check Primary   │
    │ UPDATE   │  │ App Valid?      │
    │ MODE     │  └────┬────────┬───┘
    │          │       │        │
    │ Receive  │   YES │        │ NO
    │ over     │       │        │
    │ UART     │       ▼        ▼
    │          │  ┌────────┐  ┌──────────┐
    │ Write to │  │ JUMP   │  │ Check    │
    │ Primary  │  │ TO     │  │ Secondary│
    │ Flash    │  │ PRIMARY│  │ Valid?   │
    └──────────┘  │ APP    │  └────┬─────┘
                  └────────┘       │
                      ▲        YES │
                      │            │
                      │            ▼
                      │      ┌──────────┐
                      │      │ Copy     │
                      │      │ Secondary│
                      │      │ to       │
                      │      │ Primary  │
                      └──────┴──────────┘

*/

#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

/* ========= STM32F446RE Memory Layout (512KB Flash) ======= */

#define SRAM_BASE 0x20000000UL
#define SYSTEM_MEMORY_BASE 0x1FFF0000UL
#define SRAM_END_ADDR 0x2001FFFF

// Flash geometry
#define FLASH_BASE 0x08000000UL
#define FLASH_TOTAL_SIZE (512UL * 1024UL)
#define FLASH_END_ADDR (FLASH_BASE + FLASH_TOTAL_SIZE - 1)

// Bootloader
#define BOOTLOADER_START_ADDR 0x08000000UL
#define BOOTLOADER_SIZE (32UL * 1024UL)
#define BOOTLOADER_END_ADDR (BOOTLOADER_START_ADDR + BOOTLOADER_SIZE - 1)

// Primary Application
#define PRIMARY_APP_START_ADDR 0x08008000UL
#define PRIMARY_APP_SIZE (192UL * 1024UL)
#define PRIMARY_APP_END_ADDR (PRIMARY_APP_START_ADDR + PRIMARY_APP_SIZE - 1)

// Secondary / Backup Application
#define SECONDARY_APP_START_ADDR 0x08038000UL
#define SECONDARY_APP_SIZE (192UL * 1024UL)
#define SECONDARY_APP_END_ADDR (SECONDARY_APP_START_ADDR + SECONDARY_APP_SIZE - 1)

/* ---- Firmware Headers ---- */
#define FW_HEADER_SIZE 72UL

#define PRIMARY_FW_HEADER_ADDR (PRIMARY_APP_END_ADDR - FW_HEADER_SIZE + 1)
#define SECONDARY_FW_HEADER_ADDR (SECONDARY_APP_END_ADDR - FW_HEADER_SIZE + 1)

// #if (SECONDARY_APP_END_ADDR >= (FLASH_BASE_ADDR + FLASH_TOTAL_SIZE))

// Send an error

void platform_init(void);
void blink_error_led(void);

#endif /* PLATFORM_H */
