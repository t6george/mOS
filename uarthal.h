#ifndef UART_HAL
#define UART_HAL

#include "types.h"

// Encapsulates serial port communication
class UartHal {
	public:
	static constexpr u16 com1Base = 0x3F8;
	static constexpr u8 serialEnableDlab = 0x80;
	// for simplicity, clamp the baudrate to its standard
	static constexpr u32 maxBaudRate = 115200;

	explicit UartHal(u16 dataPort);
	~UartHal() = default;
	void setBaudRate(const u32 targetBaudRate);
	void configLine() const;
	void configQueue() const;
	void configModem() const;
	u8 queueIsEmpty() const;
	void print(const i8* s) const;

	private:
	void outputChar(const i8 c) const;
	const u16 dataPort;
	const u16 queueCmdPort;
	const u16 lineCmdPort;
	const u16 modemCmdPort;
	const u16 lineStatusPort;
	u32 baudRate;
};

#endif


