# Tiva Makefile
# #####################################
#
# Part of the uCtools project
# uctools.github.com
#
#######################################
# user configuration:
#######################################
# TARGET: name of the output file
TARGET = main
# MCU: part number to build for
MCU = TM4C123GH6PM
# SOURCES: list of input source sources
SOURCES = main.cpp bsp.cpp startup_tm4c_gnu.c
# INCLUDES: list of includes, by default, use Includes directory
INCLUDES = -I$(HOME)/embedded/cmsis/Include
# OUTDIR: directory to use for output
OUTDIR = build

# LD_SCRIPT: linker script
LD_SCRIPT = $(MCU).lds

FLOAT_ABI = softfp

# define flags
CFLAGS = -g -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=$(FLOAT_ABI)
CFLAGS +=-Os -ffunction-sections -fdata-sections -MD -Wall
CFLAGS += -DPART_$(MCU) -c $(INCLUDES)
CFLAGS += -DTARGET_IS_TM4C123_RB2 -D__FPU_PRESENT
CXXFLAGS := $(CFLAGS) -std=c++11 -fno-rtti -fno-exceptions
CFLAGS += -std=c99
LDFLAGS = -T $(LD_SCRIPT) --entry Reset_Handler
LDFLAGS += --specs=nosys.specs
LDFLAGS += -mfloat-abi=$(FLOAT_ABI)

#######################################
# end of user configuration
#######################################
#
#######################################
# binaries
#######################################
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
LD = arm-none-eabi-g++
OBJCOPY = arm-none-eabi-objcopy
RM      = rm -f
MKDIR	= mkdir -p
#######################################

# list of object files, placed in the build directory regardless of source path
OBJECTS = $(addprefix $(OUTDIR)/,$(notdir $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SOURCES)))))

# default: build bin
all: $(OUTDIR)/$(TARGET).bin

$(OUTDIR)/%.o: src/%.c | $(OUTDIR)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
$(OUTDIR)/%.o: src/%.cpp | $(OUTDIR)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(OUTDIR)/a.out: $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

$(OUTDIR)/main.bin: $(OUTDIR)/a.out
	$(OBJCOPY) -O binary $< $@

# create the output directory
$(OUTDIR):
	$(MKDIR) $(OUTDIR)

clean:
	-$(RM) $(OUTDIR)/*

.PHONY: all clean
