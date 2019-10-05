#include "uarthal.h"

extern "C" void outb(u16 port, u8 val);
extern "C" void inb(u16 port);

UartHal::UartHal(u16 dataPort): dataPort(dataPort), queueCmdPort(2 + dataPort),
	lineCmdPort(3 +  dataPort), modemCmdPort(4 + dataPort),
	lineStatusPort(5 + dataPort), baudRate(MAX_BAUD_RATE) {}

void UartHal::setBaudRate(const u16 targetBaudRate) {
	// TODO: replace this with an assertion
	if (br > maxBaudRate)
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

u8 queueIsEmpty() const {
	return inb(lineStatusPort) & 0x20;
}
