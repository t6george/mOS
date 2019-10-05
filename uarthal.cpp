#include "uarthal.h"

extern "C" void outb(u16 port, u8 val);
extern "C" u8 inb(u16 port);

UartHal::UartHal(u16 dataPort): dataPort(dataPort), queueCmdPort(2 + dataPort),
	lineCmdPort(3 +  dataPort), modemCmdPort(4 + dataPort),
	lineStatusPort(5 + dataPort), baudRate(maxBaudRate) {}

void UartHal::setBaudRate(const u32 targetBaudRate) {
	// TODO: replace this with an assertion
	if (targetBaudRate > maxBaudRate)
		return;

	u16 rateFactor = maxBaudRate / targetBaudRate;
	
	outb(lineCmdPort, serialEnableDlab);
	outb(dataPort, rateFactor >> 8);
	outb(dataPort, 0x00FF & rateFactor);
}

void UartHal::configLine() const {
	// TODO: add bitfield for val written to port
	outb(lineCmdPort, 0x03);
}

void UartHal::configQueue() const {
	outb(queueCmdPort, 0xC7);
}

void UartHal::configModem() const {
	outb(modemCmdPort, 0x3);
}

u8 UartHal::queueIsEmpty() const {
	return inb(lineStatusPort) & 0x20;
}

void UartHal::outputChar(const i8 c) const {
	// spin until transmission queue is empty
	while (queueIsEmpty() == 0);
	outb(dataPort, c);
}

void UartHal::print(const i8* s) const {
	for(u16 i = 0; '\0' != s[i]; ++i)
		outputChar(s[i]);
}
