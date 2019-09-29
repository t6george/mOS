#ifndef CONSOLE_H
#define CONSOLE_H

#include "types.h"
#include "io.h"

class Console {
	static constexpr u8* consoleBuff = static_cast<u8*> 0x000B8000;
	static constexpr u8* fbCmdPort = 0x3B4;
	static constexpr u8* fbDataPort = 0x3B4;
	static constexpr setHiByte = 14;
	static constexpr setLoByte = 15;

	color defaultBg, defaultFg;
	void printChar(const u32 ind, const u8 c, const color fg, const color bg) const;
	extern void outb(u16 port, u8 val);
	
	public:

	enum Color {
		BLACK = 0,
		BLUE,
		GREEN,
		CYAN,
		DARK_GREY,
		LIGHT_BLUE,
		LIGHT_GREEN,
		LIGHT_CYAN,
		LIGHT_RED,
		LIGHT_MAGENTA,
		LIGHT_BROWN,
		WHITE
	};

	Console();
	Console(Color fg, Color bg);

	void moveFbCursor(const u16 pos) const;
	void print(const u8* s, const Color fg = defaultFg, const Color bg = defaultBg) const;
};

#endif
