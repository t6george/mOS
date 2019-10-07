#ifndef UART_HAL
#define UART_HAL

#include "types.h"
#include "src/bitfields/uartports.h"

#define SERIAL_COM1_BASE 0x3F8
#define ENABLE_DLAB 0x80

// Encapsulates serial port communication
class UartHal {
	public:
	// for simplicity, clamp the baudrate to its standard
	static constexpr u32 maxBaudRate = 115200;

	explicit UartHal(u16 dataPort);
	~UartHal();

	void setBaudRate(const u32 targetBaudRate);
	u8 queueIsEmpty();
	void print(const i8* s) ;
	void defaultUartConfig();

	private:
	void outputChar(const i8 c);

	void configLine();
	void configQueue();
	void configModem();

	const u16 dataPortAddr;
	// TODO: make these pointers (eventually unique)
	QueueCmdPort queueCmdPort;
	LineCmdPort lineCmdPort;
	ModemCmdPort modemCmdPort;
	LineStatusReg lineStatusReg;
	u32 baudRate;
};

#endif


