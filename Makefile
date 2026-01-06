# ============================
# Project
# ============================
TARGET = bootloader
BUILD  = build

# ============================
# Toolchain
# ============================
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# ============================
# MCU / CPU
# ============================
CPU     = cortex-m4
FPU     = fpv4-sp-d16
FLOAT   = hard

# ============================
# Flags
# ============================
CFLAGS = -mcpu=$(CPU) -mthumb -mfpu=$(FPU) -mfloat-abi=$(FLOAT)
CFLAGS += -O0 -g
CFLAGS += -Wall -ffreestanding -fno-builtin
CFLAGS += -DSTM32F446xx

LDFLAGS = -T bootloader/core/linker/STM32F446_BOOT.ld
LDFLAGS += -nostartfiles -Wl,--gc-sections

# ============================
# Include paths
# ============================
INCLUDES = \
-Ibootloader/core/inc \
-IDrivers/CMSIS/Include \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include

# ============================
# Sources
# ============================
SRCS = \
bootloader/core/src/main.c \
bootloader/core/src/bootloader.c \
bootloader/core/src/flash_if.c \
bootloader/core/src/jump.c \
bootloader/core/src/platform.c \
bootloader/startup/startup_stm32f446xx.s
SRCS += bootloader/core/src/system_stm32f4xx.c


OBJS = $(SRCS:%.c=$(BUILD)/%.o)
OBJS := $(OBJS:%.s=$(BUILD)/%.o)

# ============================
# Rules
# ============================
all: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).bin

$(BUILD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

$(BUILD)/bootloader/startup/startup_stm32f446xx.o: bootloader/startup/startup_stm32f446xx.s
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@


$(BUILD)/$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) \
	-nostdlib -nostartfiles \
	-o $@


$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD)



