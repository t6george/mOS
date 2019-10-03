#ifndef UART_HAL
#define UART_HAL

#include "types.h"

// Encapsulates serial port communication
class UartHal {
	public:
	static constexpr u16 com1Base = 0x3F8;
	static constexpr u8 serialEnableDlab = 0x80;
	static constexpr u16 maxBaudRate = 115200.0;

	UartHal(u16 dataPort);
	~UartHal() = default;
	void setBaudRate(const u16 targetBaudRate);
	void configLine() const;
	private:
	const u16 dataPort;
	const u16 queueCmdPort;
	const u16 lineCmdPort;
	const u16 modemCmdPort;
	const u16 lineStatusPort;
	unsigned double baudRate;
}

#endif

extern "C" void outb(u16 port, u8 val);

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



