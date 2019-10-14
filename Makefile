BUILD_DIR ?= build
SRC_DIR ?= src
HEADER_DIR ?= include

SOURCES := $(shell find . -name "*.cpp" -or -name "*.s")
OBJECTS := $(addsuffix .o,$(basename $(SOURCES)))
INCLUDES := $(shell find include -type d | sed s/^/-I/)

CPPC = g++
CPPFLAGS = -m32 -g -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti -Wall -Werror -I./src/bitfields -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
	    -b boot/grub/stage2_eltorito    \
	    -no-emul-boot                   \
	    -boot-load-size 4               \
	    -A os                           \
	    -input-charset utf8             \
	    -quiet                          \
	    -boot-info-table                \
	    -o os.iso                       \
	    iso

run: os.iso
	echo $(INCLUDES)
	bochs -f bochsrc.txt -q

%.o: %.cpp
	$(CPPC) $(CPPFLAGS)  $< -o $@ -lstdc++ $(INCLUDES)

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o *.out kernel.elf os.iso

