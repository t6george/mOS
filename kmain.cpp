#include "console.h"

extern "C" int kmain () {
	Console console;
	i8 s[11] = {'H','e','l','l','o',' ','M', 'o', 's', 's','\0'};
	console.print(s);
	return 0;
}


