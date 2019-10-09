#include "console.h"
#include "uarthal.h"
#include "gdt.h"

extern "C" int kmain () {
	Console console;
	UartHal uart(SERIAL_COM1_BASE);
	i8 s[11] = {'H','e','l','l','o',' ','M', 'o', 's', 's','\0'};
	console.print(s);
	uart.defaultUartConfig();
	uart.print(s);

	GlobalDescriptorTable gdt;
	gdt.initNullDescriptor();
	gdt.initCodeDescriptor();
	gdt.initDataDescriptor();
	gdt.writeGdt();


	return 0;
}


