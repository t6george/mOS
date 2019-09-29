GPP_PARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASM_PARAMS = --32
LD_PARAMS = -melf_i386

OBJS = loader.o kernel.o

%.o: %.cpp
	g++ $(GPP_PARAMS) -o $@ -c $<

%.o: %.s
	as $(ASM_PARAMS) -o $@ $<

mykernel.bin: linker.ld $(OBJS)
	ld $(LD_PARAMS) -T $< -o $@ $(OBJS)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

mykernel.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso
run: mykernel.iso
	(killall VirtualBox && sleep 1)|| true
	VirtualBox --start "My operating System" &
