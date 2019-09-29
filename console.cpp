#include "console.h"

extern void outb(u16 port, u8 val);

static u8* Console::frameBuffer = reinterpret_cast<u8*>(0x000B8000);
static u8* Console::fbCmdPort = reinterpret_cast<u8*>(0x3B4);
static u8* Console::fbDataPort = reinterpret_cast<u8*>(0x3B5);

Console::Console(): defaultBg(Console::Black), defaultFg(Console::GREEN) {}

Console::Console(Console::Color fg, Console::Color bg): defaultBg(bg), defaultFg(fg) {}

void inline Console::moveFbCursor(const u16 pos) const {
	*fbCmdPort = setHiByte;
	*fbDataPort = pos >> 8;

	*fbCmdPort = setLoByte;
	*fbDataPort = 0x00FF & pos;
}

void inline Console::printChar(const u32 ind, const u8 c, Console::Color fg, Console::Color bg) const {
	frameBuffer[i] = c;
	frameBuffer[1+i] = (fg << 4) | bg;
}

void Console::print(const u8* s) const {
	for (u16 i = 0; '\0' != s[i]; ++i)
		printChar(i, s[i], defaultFg, defaultBg);

}

void Console::print(const u8* s, const Color fg, const Color bg) const {
	for (u16 i = 0; '\0' != s[i]; ++i)
		printChar(i, s[i], fg, bg);

}
