##########################################################################################################################

# ------------------------------------------------
# Makefile for GNU and Arm Compiler 6
#
# helay
# 2019-08-01
# ------------------------------------------------

######################################
# target
######################################
TARGET = STM32F429IGT
#COMPLIE_LLVM
COMPLIE_LLVM = 0
#COMPLIE_GNU
COMPLIE_GNU = 1
#LLVM_VERSION    #llvm version lower than 6.12, clang cannot compile asm
#llvm lower than 6.12, turn off
ASM_BY_CLANG = 1

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build
CORE = ../Core
HAL_LIB = ../Drivers/STM32F4xx_HAL_Driver
BSP = ../BSP

######################################
# source
######################################
# C sources
C_SOURCES =  \
$(CORE)/Src/main.c \
$(CORE)/Src/stm32f4xx_it.c \
$(CORE)/Src/stm32f4xx_hal_msp.c \
$(HAL_LIB)/Src/stm32f4xx_hal_rtc.c \
$(HAL_LIB)/Src/stm32f4xx_hal_rtc_ex.c \
$(HAL_LIB)/Src/stm32f4xx_hal_tim.c \
$(HAL_LIB)/Src/stm32f4xx_hal_tim_ex.c \
$(HAL_LIB)/Src/stm32f4xx_hal_rcc.c \
$(HAL_LIB)/Src/stm32f4xx_hal_rcc_ex.c \
$(HAL_LIB)/Src/stm32f4xx_hal_flash.c \
$(HAL_LIB)/Src/stm32f4xx_hal_flash_ex.c \
$(HAL_LIB)/Src/stm32f4xx_hal_flash_ramfunc.c \
$(HAL_LIB)/Src/stm32f4xx_hal_gpio.c \
$(HAL_LIB)/Src/stm32f4xx_hal_dma_ex.c \
$(HAL_LIB)/Src/stm32f4xx_hal_dma.c \
$(HAL_LIB)/Src/stm32f4xx_hal_pwr.c \
$(HAL_LIB)/Src/stm32f4xx_hal_pwr_ex.c \
$(HAL_LIB)/Src/stm32f4xx_hal_cortex.c \
$(HAL_LIB)/Src/stm32f4xx_hal.c \
$(HAL_LIB)/Src/stm32f4xx_hal_exti.c \
$(HAL_LIB)/Src/stm32f4xx_hal_uart.c \
$(HAL_LIB)/Src/system_stm32f4xx.c \
$(BSP)/printf_support.c

# ASM sources
#COMPLIE_LLVM
ifeq ($(COMPLIE_LLVM), 1) 
	ASM_SOURCES =  \
	startup_stm32f429xx-arm.s
#COMPLIE_GNU
else
	ASM_SOURCES =  \
	startup_stm32f429xx-gcc.s
endif

#######################################
# binaries
#######################################
#COMPLIE_LLVM
ifeq ($(COMPLIE_LLVM), 1) 
	PREFIX = arm
	ifdef LLVM_PATH
		CC = $(LLVM_PATH)/$(PREFIX)clang
		ifeq ($(ASM_BY_CLANG), 1) 
			AS = $(LLVM_PATH)/$(PREFIX)clang
		else
			AS = $(LLVM_PATH)/$(PREFIX)asm
		endif
		CP = $(LLVM_PATH)/fromelf
		LK = $(LLVM_PATH)/$(PREFIX)link
	else
		CC = $(PREFIX)clang
		ifeq ($(ASM_BY_CLANG), 1) 
			AS = $(PREFIX)clang
		else
			AS = $(PREFIX)asm
		endif
		CP = fromelf
		LK = $(PREFIX)link
	endif
	
	ELF = $(CP) --elf --privacy #outfile.axf infile.axf
	BIN = $(CP) --bin #outfile.bin infile.axf
	HEX = $(CP) --i32 #outfile.bin infile.axf

#COMPLIE_GNU
else
	PREFIX = arm-none-eabi-
	# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
	# either it can be added to the PATH environment variable.
	ifdef GCC_PATH
		CC = $(GCC_PATH)/$(PREFIX)gcc
		AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
		CP = $(GCC_PATH)/$(PREFIX)objcopy
		SZ = $(GCC_PATH)/$(PREFIX)size
	else
		CC = $(PREFIX)gcc
		AS = $(PREFIX)gcc -x assembler-with-cpp
		CP = $(PREFIX)objcopy
		SZ = $(PREFIX)size
	endif
	HEX = $(CP) -O ihex
	BIN = $(CP) -O binary -S
endif

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
#COMPLIE_LLVM
ifeq ($(COMPLIE_LLVM), 1) 
	MCU = --target=arm-arm-none-eabi $(CPU) -mthumb $(FPU) $(FLOAT-ABI) -mlittle-endian
#COMPLIE_GNU
else
	MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
endif

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F429xx

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-I$(CORE)/Inc \
-I$(HAL_LIB)/Inc \
-I$(HAL_LIB)/Inc/Legacy \
-I../Drivers/CMSIS/Device/ST/STM32F4xx/Include \
-I../Drivers/CMSIS/Include \
-I../BSP

# compile gcc flags
# C FLAGS
C_LIB = -std=gnu11
C_WARN_ERROR = -Wno-packed -Wno-missing-variable-declarations -Wno-missing-prototypes \
-Wno-missing-noreturn -Wno-sign-conversion -Wno-nonportable-include-path \
-Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command \
-Wno-documentation -Wno-license-management -Wno-parentheses-equality
#COMPLIE_LLVM
ifeq ($(COMPLIE_LLVM), 1)
	C_CONFIG = -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Wall
#COMPLIE_GNU
else
	C_CONFIG = -Wall -fdata-sections -ffunction-sections
endif
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) $(C_LIB) $(C_CONFIG) 

# A FLAGS
ifeq ($(ASM_BY_CLANG), 1) 
	ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
else
	ASFLAGS = --debug --xref --diag_suppress=9931 --cpu=Cortex-M4.fp $(AS_DEFS) $(AS_INCLUDES)
endif

#DEBUG
ifeq ($(DEBUG), 1)
	#COMPLIE_LLVM
	ifeq ($(COMPLIE_LLVM), 1) 
		CFLAGS += -g -gdwarf-3
	#COMPLIE_GNU
	else #COMPLIE_GNU
		CFLAGS += -g -gdwarf-2
	endif
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################
# link script
#COMPLIE_LLVM
ifeq ($(COMPLIE_LLVM), 1) 
LDSCRIPT = STM32F429IGT.sct
#COMPLIE_GNU
else
LDSCRIPT = STM32F429IGTx_FLASH.ld
endif

# libraries
#COMPLIE_LLVM
ifeq ($(COMPLIE_LLVM), 1) 
LDFLAGS = --entry=Reset_Handler --scatter=$(LDSCRIPT) --info=sizes --strict 
#COMPLIE_GNU
else
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
endif

# default action: build all
#COMPLIE_LLVM
ifeq ($(COMPLIE_LLVM), 1) 
all: $(BUILD_DIR)/$(TARGET).axf $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
#COMPLIE_GNU
else 
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
endif

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

#COMPLIE_LLVM
ifeq ($(COMPLIE_LLVM), 1) 
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c -xc $(CFLAGS) $< -o $@

ifeq ($(ASM_BY_CLANG), 1) 
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS)  -x assembler-with-cpp  -masm=auto $< -o $@ 
else
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@ 
endif

$(BUILD_DIR)/$(TARGET).axf: $(OBJECTS) $(LDSCRIPT) $(USER_OBJS) 
	$(LK) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.axf | $(BUILD_DIR)
	$(ELF) --output=$@ $< 

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.axf | $(BUILD_DIR)
	$(HEX) --output=$@ $< 
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.axf | $(BUILD_DIR)
	$(BIN) --output=$@ $< 

#COMPLIE_GNU
else
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	

endif

$(BUILD_DIR):
	mkdir $@
#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***