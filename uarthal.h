#ifndef UART_HAL
#define UART_HAL

#include "types.h"
#include <uartports.h>

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
	u8 queueIsEmpty() const;
	void print(const i8* s) const;

	private:
	void outputChar(const i8 c) const;

	namespace defaultCfg {
		void configLine() const;
		void configQueue() const;
		void configModem() const;
	}

	const u16 dataPortAddr;
	QueueCmdPort* queueCmdPort;
	LineCmdPort* lineCmdPort;
	ModemCmdPort* modemCmdPort;
	LineStatusReg* lineStatusPort;
	u32 baudRate;
};

#endif


