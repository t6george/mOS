#ifndef UART_PORTS
#define UART_PORTS

#include "../../types.h"

typedef struct LineCmdPort {
	LineCmdPort(const u16 addr): addr{addr}, contents.raw{0} {}
	typedef union {
		u8 raw;
		struct fields {
			u8 dataLen: 2;
			u8 stop   : 1;
			u8 parity : 3;
			u8 br     : 1;
			u8 dlab   : 1;
		};
	} Contents;
	const u16 addr;
	Contents contents;
} LineCmdPort;

typedef struct QueueCmdPort {
	QueueCmdPort(const u16 addr): addr{addr}, contents.raw{0} {}
	typedef union {
		u8 raw;
		struct fields {
			u8 enableQ     : 1;
			u8 clReceiveQ  : 1;
			u8 clTransmitQ : 1;
			u8 dmaMode     : 1;
			u8 reserved    : 1;
			u8 buffSize    : 1;
			u8 qSize       : 2;
		};
	} Contents;
	const u16 addr;
	Contents contents;
} QueueCmdPort;

typedef struct {
	ModemCmdPort(const u16 addr): addr{addr}, contents.raw{0} {}
	typedef union {
		u8 raw;
		struct fields {
			u8 dtr      : 1;
			u8 rts      : 1;
			u8 ao1      : 1;
			u8 ao2      : 1;
			u8 loopBack : 1;
			u8 autoFlow : 1;
			u8 reserved : 2;
		};
	} Contents;
	const u16 addr;
	Contents contents;
} ModemCmdPort;

typedef struct LineStatusReg {
	LineStatusReg(const u16 addr): addr{addr}, contents.raw{0} {}
	typedef union {
		u8 raw;
		struct fields {
			u8 dataReady      : 1;
			u8 overrunE       : 1;
			u8 parityE        : 1;
			u8 framingE       : 1;
			u8 breakIndicator : 1;
			u8 thre           : 1;
			u8 temt           : 1;
			u8 impendingE     : 1;
		};
	} Contents;
	const u16 addr;
	Contents contents;
} LineStatusReg;

#endif
