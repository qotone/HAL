######################################
# STM32F10x Makefile for GNU toolchain and stm32flash
# Usage:
######################################

######################################
# target
######################################
TARGET = demo

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# build for debug in ram?
RAMBUILD = 0
# optimization
OPT = -O0

#######################################
# paths
#######################################
# source path
VPATH = src startup

WORKSPACE_DIR = ../../../
FATFSPATH = $(WORKSPACE_DIR)/thirdparty/fatfs
HAL_DIR = $(WORKSPACE_DIR)/HAL


VPATH += $(PERIPHLIBPATH)/CMSIS/Device/ST/STM32F10x
VPATH += $(PERIPHLIBPATH)/src
VPATH += $(HAL_DIR)/src

# ------------FATFS 
PERIPHLIBPATH = $(WORKSPACE_DIR)/STM32F10x_StdPeriph_Driver
VPATH += $(FATFSPATH)
VPATH += $(FATFSPATH)/drivers
VPATH += $(FATFSPATH)/option


# Build path
BUILD_DIR = build

# #####################################
# source
# #####################################
SRCS = \
  main.c \
  stm32f10x_it.c \
  system_stm32f10x.c \
  retarget.c \
  rtc_api.c

SRCSASM = \
  startup_stm32f10x_hd.s 

# #####################################
# firmware library
# #####################################
PERIPHLIB_SOURCES = \
  stm32f10x_gpio.c \
  stm32f10x_rcc.c \
  stm32f10x_usart.c \
misc.c \
stm32f10x_bkp.c \
stm32f10x_pwr.c \
stm32f10x_rtc.c 
#core_cm3.c #comment in v3.6

#######################################
# binaries
#######################################
ARM_GCC_PATH = /home/luoyang/arm-none-eabi-gcc/gcc-arm-none-eabi-4_9-2014q4/bin
CC = $(ARM_GCC_PATH)/arm-none-eabi-gcc
AS = $(ARM_GCC_PATH)/arm-none-eabi-gcc -x assembler-with-cpp
CP = $(ARM_GCC_PATH)/arm-none-eabi-objcopy
AR = $(ARM_GCC_PATH)/arm-none-eabi-ar
SZ = $(ARM_GCC_PATH)/arm-none-eabi-size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# macros for gcc
DEFS = -DSTM32F10X_HD -DUSE_STDPERIPH_DRIVER
ifeq ($(RAMBUILD), 1)
DEFS += -DVECT_TAB_SRAM
endif
ifeq ($(DEBUG), 1)
DEFS += -DDEBUG -D_DEBUG
endif
# includes for gcc
INCLUDES = -Iinc
# for v3.6
INCLUDES += -I$(PERIPHLIBPATH)/CMSIS/Include
INCLUDES += -I$(PERIPHLIBPATH)/CMSIS/Device/ST/STM32F10x
INCLUDES += -I$(PERIPHLIBPATH)/inc

# ------ HAL ----------
INCLUDES += -I$(HAL_DIR)/inc
# ------FATFS ----------
INCLUDES += -I$(FATFSPATH)
INCLUDES += -I$(FATFSPATH)/drivers
INCLUDES += -I$(FATFSPATH)/option

# compile gcc flags
CFLAGS = -mthumb -mcpu=cortex-m3 $(DEFS) $(INCLUDES) $(OPT) -Wall -mfix-cortex-m3-ldrd -fsigned-char -ffunction-sections -fdata-sections -c -std=c99
ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif
# Generate dependency information
CFLAGS += -MD -MP -MF .dep/$(@F).d

#######################################
# LDFLAGS
#######################################
# link script
ifeq ($(RAMBUILD), 1)
LDSCRIPT = linker/STM32F103VE_ram.ld
else
LDSCRIPT = linker/STM32F103VE_flash.ld
endif
# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = -mthumb -mcpu=cortex-m3 -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -mfix-cortex-m3-ldrd


# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex


#######################################
# build the application
#######################################
# list of firmware library objects
PERIPHLIB_OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(PERIPHLIB_SOURCES:.c=.o)))
# list of C program objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.c=.o)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(SRCSASM:.s=.o)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) $(PERIPHLIB_OBJECTS) Makefile
	$(CC) $(OBJECTS) $(PERIPHLIB_OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@
$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
$(BUILD_DIR):
	mkdir -p $@

######################################
# flash the chip with stm32flash
######################################
flash:
	stm32flash -w $(BUILD_DIR)/$(TARGET).hex -g 0x0  /dev/ttyUSB0


#######################################
# delete all user application files
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)

#
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***
