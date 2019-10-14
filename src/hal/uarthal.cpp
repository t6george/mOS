#include "uarthal.h"

extern "C" void outb(u16 port, u8 val);
extern "C" u8 inb(u16 port);

UartHal::UartHal(u16 dataPort): dataPortAddr{dataPort}, queueCmdPort{QueueCmdPort(2+ dataPort)},
	lineCmdPort{LineCmdPort(3 + dataPort)}, modemCmdPort{ModemCmdPort(4 + dataPort)},
	lineStatusReg{LineStatusReg(5 + dataPort)}, baudRate{maxBaudRate} {}




UartHal::~UartHal() {
	// delete queueCmdPort;
	// delete lineCmdPort;
	// delete modemCmdPort;
	// delete lineStatusReg;
}

void UartHal::setBaudRate(const u32 targetBaudRate) {
	// TODO: replace this with an assertion
	if (targetBaudRate > maxBaudRate)
		return;

	u16 rateFactor = maxBaudRate / targetBaudRate;
	
	outb(lineCmdPort.addr, ENABLE_DLAB);
	outb(dataPortAddr, rateFactor >> 8);
	outb(dataPortAddr, 0x00FF & rateFactor);
}

void UartHal::configLine() {
	lineCmdPort.contents.dataLen = 0x3;

	outb(lineCmdPort.addr, lineCmdPort.contents.raw);
}

void UartHal::configQueue() {
	queueCmdPort.contents.enableQ = 0x1;
	queueCmdPort.contents.clReceiveQ = 0x1;
	queueCmdPort.contents.clTransmitQ = 0x1;

	// 14 byte queue size
	queueCmdPort.contents.qSize = 0x3;

	outb(queueCmdPort.addr, queueCmdPort.contents.raw);
}

void UartHal::configModem() {
	modemCmdPort.contents.dtr = 0x1;
	modemCmdPort.contents.rts = 0x1;

	outb(modemCmdPort.addr, modemCmdPort.contents.raw);
}

void UartHal::defaultUartConfig() {
	configLine();
	configQueue();
	configModem();
}

u8 UartHal::queueIsEmpty() {
	lineStatusReg.contents.raw = inb(lineStatusReg.addr);
	return lineStatusReg.contents.thre;
}

void UartHal::outputChar(const i8 c) {
	// spin until transmission queue is empty
	while (queueIsEmpty() == 0);
	outb(dataPortAddr, c);
}

void UartHal::print(const i8* s) {
	for(u16 i = 0; '\0' != s[i]; ++i)
		outputChar(s[i]);
}
