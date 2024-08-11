# Target platform (currently armv6, armv8a, and atmega328)
TARGET ?= armv6

# The toolchain to use. arm-none-eabi works, but there does exist 
# arm-bcm2708-linux-gnueabi.
GNU ?= arm-none-eabi

# Basic C-Compiler Flags for all targets
CCFLAGS=-Wall -ffreestanding -nostdlib -fno-builtin

ifeq ($(TARGET),atmega328)
CCFLAGS+=-mmcu=atmega328
GNU=avr
endif

ifeq ($(TARGET),armv6)
CCFLAGS+=-march=armv6
endif

ifeq ($(TARGET),armv8a)
CCFLAGS+=-march=armv8-a
endif

ifdef DEBUG
CCFLAGS += -g -O0
endif

# The intermediate directory for compiled object files.
BUILD = build/

# The directory in which source files are stored.
SOURCE = src/

INCLUDE = src/

# The name of the output file to generate.
BINARY = baeros.img

# The name of the assembler listing file to generate.
LIST = nucleus.list

# The name of the map file to generate.
MAP = nucleus.map

# The name of the linker script to use.
LINKER = nucleus.ld

# The names of all object files that must be generated. Deduced from the 
# assembly code files in source.
OBJECTS := $(patsubst $(SOURCE)%.s,$(BUILD)%.o,$(wildcard $(SOURCE)*.s)) \
			$(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c)) \
			$(patsubst $(SOURCE)arch/$(TARGET)/%.s,$(BUILD)%.o,$(wildcard $(SOURCE)arch/$(TARGET)/*.s))

# $(info Found source files: $(wildcard $(SOURCE)arch/$(TARGET)/*.s))

# Rule to make everything.
all: $(BINARY) $(LIST)

# Rule to remake everything. Does not include clean.
rebuild: all

# Rule to make the listing file.
$(LIST) : $(BUILD)output.elf
	$(GNU)-objdump -D $(BUILD)output.elf > $(LIST)

# Rule to make the image file.
$(BINARY) : $(BUILD)output.elf
	$(GNU)-objcopy $(BUILD)output.elf -O binary $(BINARY) 

# Rule to make the elf file.
$(BUILD)output.elf : $(OBJECTS) $(LINKER)
	$(GNU)-ld --no-undefined $(OBJECTS) -Map $(MAP) -o $(BUILD)output.elf -T $(LINKER)

$(BUILD):
	mkdir $@

# Rules to make the object files.
$(BUILD)%.o: $(SOURCE)%.s $(BUILD)
	$(GNU)-as -I $(SOURCE) $< -o $@

$(BUILD)%.o: $(SOURCE)arch/$(TARGET)/%.s
	$(GNU)-as -I $(SOURCE) $< -o $@

$(BUILD)%.o: $(SOURCE)%.c $(BUILD)
	$(GNU)-gcc $(CCFLAGS) -I$(INCLUDE) -c $< -o $@ 

# Rule to clean files.
clean : 
	-rm -rf $(BUILD)
	-rm -f $(BINARY)
	-rm -f $(LIST)
	-rm -f $(MAP)
