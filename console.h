#include "types.h"

extern void outb(u16 portAddr, u8 data);
#define CONSOLE_ADDR 0x000B8000

class Console {
	enum color {
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

	static constexpr u32 consoleBaseAddr = 0x000B8000;
	static constexpr u16 fbCmdPort = 0x3B4;
	static constexpr u16 fbDataPort = 0x3B4;
	static constexpr setHiByte = 14;
	static constexpr setLoByte = 15;

	color defaultBg, defaultFg;

	public:

	void moveFbCursor(const u16 pos) const;
	void printChar(const u32 ind, const u8 c, const color fg, const color bg) const;
	void print(const u8* s, const color fg = defaultFg, const color bg = defaultBg) const;
};

void printChar(unsigned int ind, const char c, CONSOLE fg, CONSOLE bg) {
	char *fb = static_cast<char*> CONSOLE_ADDR;
	fb[i] = c;
	fb[1+i] = (fg << 4) | bg;
}


