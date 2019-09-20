GPP_PARAMS = -m32
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

