#include "console.h"
#include "uarthal.h"

#define SERIAL_COM1_BASE 0x3F8

extern "C" int kmain () {
	Console console;
	UartHal uart(SERIAL_COM1_BASE);
	i8 s[11] = {'H','e','l','l','o',' ','M', 'o', 's', 's','\0'};
	console.print(s);
	uart.configLine();
	uart.configQueue();
	uart.configModem();
	uart.print(s);
	return 0;
}


