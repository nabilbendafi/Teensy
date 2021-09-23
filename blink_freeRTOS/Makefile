GCC_BIN = 
PROJECT = blink_freeRTOS
HAL_DIR = ../mbed/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX
MBED_COMMON = ../mbed/libraries/mbed/common
CMSIS = ../mbed/libraries/mbed/targets/cmsis
OBJECTS = src/main.o \
	./src/FreeRTOS/Source/portable/GCC/TEENSY3_1/port.o \
	../freertos/croutine.o \
	../freertos/event_groups.o \
	../freertos/list.o \
	../freertos/queue.o \
	../freertos/tasks.o \
	../freertos/timers.o \
	../freertos/portable/MemMang/heap_2.o \
	$(CMSIS)/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/TOOLCHAIN_GCC_ARM/startup_MK20DX256.o \
	$(CMSIS)/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/system_MK20DX256.o
SYS_OBJECTS = 
INCLUDE_PATHS = -I. \
	-I./include \
	-I$(CMSIS) -I$(CMSIS)/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/ \
	-I../mbed/libraries/mbed/api \
	-I../mbed/libraries/mbed \
	-I../mbed/libraries/mbed/targets \
	-I../mbed/libraries/mbed/targets/cmsis \
	-I../mbed/libraries/mbed/targets/cmsis/TARGET_Freescale \
	-I../mbed/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20XX \
	-I../mbed/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1 \
	-I../mbed/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/TOOLCHAIN_GCC_ARM \
	-I../mbed/libraries/mbed/targets/hal \
	-I../mbed/libraries/mbed/targets/hal/TARGET_Freescale \
	-I../mbed/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX \
	-I../mbed/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1 \
	-I../mbed/libraries/mbed/api \
	-I../mbed/libraries/mbed/hal \
	-I $(HAL_DIR)/TARGET_TEENSY3_1 \
	-I./src/FreeRTOS/Source/portable/GCC/TEENSY3_1 \
	-I../freertos/include
LIBRARY_PATHS = 
LIBRARIES = 
LINKER_SCRIPT = $(CMSIS)/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/TOOLCHAIN_GCC_ARM/MK20DX256.ld

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

all: $(PROJECT).bin $(PROJECT).hex size


clean:
	rm -f $(PROJECT).bin $(PROJECT).elf $(PROJECT).hex $(PROJECT).map $(PROJECT).lst $(OBJECTS) $(DEPS)


.asm.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<
.s.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<
.S.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<

.c.o:
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99   $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 -fno-rtti $(INCLUDE_PATHS) -o $@ $<



$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS)
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS)


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
