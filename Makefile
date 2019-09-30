OBJECTS = loader.o console.o io.o kmain.o
CC = g++
CFLAGS = -m32 -g -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti -c
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
	bochs -f bochsrc.txt -q

%.o: %.cpp
	$(CC) $(CFLAGS)  $< -o $@ -lstdc++

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso

