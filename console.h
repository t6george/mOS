#ifndef CONSOLE_H
#define CONSOLE_H

#include "types.h"

class Console {
	public:

	enum class Color {
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
	~Console() = default;

	void moveFbCursor(const u16 pos) const;
	void print(const i8*s) const;
	void print(const i8* s, const Color fg, const Color bg) const;

	static constexpr u8 setHiByte = 14;
	static constexpr u8 setLoByte = 15;
	static constexpr u16 fbCmdPort = 0x03B4;
	static constexpr u16 fbDataPort = 0x03B5;
	static u8* frameBuffer;

	private:

	Color defaultBg, defaultFg;
	
	void printChar(const u32 ind, const i8 c, const Color fg, const Color bg) const;
		
};

#endif
