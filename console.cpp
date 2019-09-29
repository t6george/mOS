#include "console.h"

Console::Console(): defaultBg(Console::Black), defaultFg(Console::GREEN) {}

Console::Console(Console::Color fg, Console::Color bg): defaultBg(bg), defaultFg(fg) {}

void inline Console::moveFbCursor(const u16 pos) const {
	*fbCmdPort = setHiByte;
	*fbDataPort = pos >> 8;

	*fbCmdPort = setLoByte;
	*fbDataPort = 0x00FF & pos;
}

void inline Console::printChar(const u32 ind, const u8 c, Console::Color fg, Console::Color bg) const {
	fb[i] = c;
	fb[1+i] = (fg << 4) | bg;
}

void Console::print(const u8* s, const Color fg = defaultFg, const Color bg = defaultBg) const {
	for (u16 i = 0; '\0' != s[i]; ++i)
		printChar(i, s[i], fg, bg);

}
