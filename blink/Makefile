GCC_BIN = 
PROJECT = blink
CMSIS = ../mbed/cmsis
TARGETS = ../mbed/targets
OBJECTS = blink.o \
	$(TARGETS)/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/device/TOOLCHAIN_GCC_ARM/startup_MK20DX256.o \
	$(TARGETS)/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/device/system_MK20DX256.o
SYS_OBJECTS = 
INCLUDE_PATHS = -I. \
	-I$(CMSIS)/TARGET_CORTEX_M \
	-I$(TARGETS)/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/device
LIBRARY_PATHS = 
LIBRARIES = 
LINKER_SCRIPT = $(TARGETS)/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/device/TOOLCHAIN_GCC_ARM/MK20DX256.ld

############################################################################### 
AS      = $(GCC_BIN)arm-none-eabi-as
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
OBJDUMP = $(GCC_BIN)arm-none-eabi-objdump
SIZE    = $(GCC_BIN)arm-none-eabi-size

CPU = -mcpu=cortex-m4 -mthumb
CC_FLAGS = $(CPU) -c -g -fno-common -fmessage-length=0 -Wall -Wextra -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -MMD -MP
CC_SYMBOLS = -DTARGET_TEENSY3_1 -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -DTARGET_K20DX256 -DTARGET_CORTEX_M -DTARGET_Freescale -DTARGET_M4 -D__CORTEX_M4 -DARM_MATH_CM4 -DTARGET_K20XX 

LD_FLAGS = $(CPU) -Wl,--gc-sections --specs=nosys.specs -u _printf_float -u _scanf_float -Wl,-Map=$(PROJECT).map,--cref
LD_SYS_LIBS = 


ifeq ($(DEBUG), 1)
  CC_FLAGS += -DDEBUG -O0
else
  CC_FLAGS += -DNDEBUG -Os
endif

.PHONY: all clean lst size

all: $(LINKER_SCRIPT:.ld=.gen) $(PROJECT).bin $(PROJECT).hex size


clean:
	rm -f $(PROJECT).bin $(PROJECT).elf $(PROJECT).hex $(PROJECT).map $(PROJECT).lst $(LINKER_SCRIPT:.ld=.gen) $(OBJECTS) $(DEPS)

.asm.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<
.s.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<
.S.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<

.c.o:
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99  $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 -fno-rtti $(INCLUDE_PATHS) -o $@ $<

%.gen: %.ld
	$(CC) -E -CC -x c $< | grep -v "^#" > $@

$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS)
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT:.ld=.gen) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS)

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

$(PROJECT).hex: $(PROJECT).elf
	@$(OBJCOPY) -O ihex $< $@

$(PROJECT).lst: $(PROJECT).elf
	@$(OBJDUMP) -Sdh $< > $@

lst: $(PROJECT).lst

size: $(PROJECT).elf
	$(SIZE) $(PROJECT).elf

DEPS = $(OBJECTS:.o=.d) $(SYS_OBJECTS:.o=.d)
-include $(DEPS)
