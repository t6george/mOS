#include "console.h"

extern "C" int kmain () {
	Console console;
	i8 s[3];
	s[0] = 'h';
	s[1] = 'i';
	s[2] = '\0';
	console.print(s);
	return 0;
}


