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
	void configQueue() const;
	void configModem() const;
	u8 queueIsEmpty() const;
	private:
	const u16 dataPort;
	const u16 queueCmdPort;
	const u16 lineCmdPort;
	const u16 modemCmdPort;
	const u16 lineStatusPort;
	unsigned double baudRate;
}

#endif


