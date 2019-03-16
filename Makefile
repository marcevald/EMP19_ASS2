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
MCU = tm4c123gh6pm
# INCLUDES: list of includes, by default, use Includes directory
INCLUDES = -IInclude 
# OUTDIR: directory to use for output
OUTDIR = build
# SOURCES: list of input source sources
SOURCES = main.c systick.c tm4c123gh6pm_startup_ccs_gcc.c btn.c gpio.c led_driver.c traffic_light.c

# LD_SCRIPT: linker script
LD_SCRIPT = $(MCU).lds

# define flags
CFLAGS = -g -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
CFLAGS +=-O0 -MD -std=c99 -Wall -ffunction-sections -fdata-sections 
CFLAGS += -pedantic -DPART_$(MCU) -c 
CFLAGS += -DTARGET_IS_BLIZZARD_RA1
LDFLAGS = -T $(LD_SCRIPT) --entry ResetISR --gc-sections

#######################################
# end of user configuration
#######################################
#
#######################################
# binaries
#######################################
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
RM      = rm -f
MKDIR	= mkdir -p
#######################################

# list of object files, placed in the build directory regardless of source path
OBJECTS = $(addprefix $(OUTDIR)/,$(notdir $(SOURCES:.c=.o)))

# default: build bin
all: $(OUTDIR)/$(TARGET).bin

$(OUTDIR)/%.o: src/%.c | $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/a.out: $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

$(OUTDIR)/main.bin: $(OUTDIR)/a.out
	$(OBJCOPY) -O binary $< $@

# create the output directory
$(OUTDIR):
	$(MKDIR) $(OUTDIR)

flash:
	make
	lm4flash $(OUTDIR)/$(TARGET).bin

clean:
	-$(RM) $(OUTDIR)/*

.PHONY: all clean
