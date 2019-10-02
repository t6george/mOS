#include "console.h"

extern "C" void outb(u16 port, u8 val);

u8* Console::frameBuffer = (u8*)(0x000B8000);

Console::Console(): defaultBg(Console::Color::BLACK), defaultFg(Console::Color::GREEN) {}

Console::Console(Console::Color fg, Console::Color bg): defaultBg(bg), defaultFg(fg) {}

Console::~Console() {}

void inline Console::moveFbCursor(const u16 pos) const {
	outb(fbCmdPort, setHiByte);
	outb(fbDataPort, (u8)(pos >> 8));

	outb(fbCmdPort, setLoByte);
	outb(fbDataPort, (u8)pos);
}

void inline Console::printChar(const u32 ind, const i8 c, Console::Color fg, Console::Color bg) const {
	frameBuffer[ind] = c;
	frameBuffer[1+ind] = (((u8)bg) << 4) | ((u8)fg);
}

void Console::print(const i8* s) const {
	u16 i = 0;
	for (; '\0' != s[i]; ++i) {
		printChar(2*i + 50, s[i], defaultFg, defaultBg);
		moveFbCursor(i);
	}
}

//void Console::print(const i8* s, const Color fg, const Color bg) const {
//	u16 i = 0;
//	for (; '\0' != s[i]; ++i)
//		printChar(i, s[i], fg, bg);
//}
