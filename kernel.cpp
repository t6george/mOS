#include "types.h"

void printf(const char *s) {
	uint16_t* stdout = (uint16_t*) 0xb8000;
	for (int i = 0; *(s+i) != '\0'; ++i)
		*stdout = (*stdout & 0xFF00) | *(s+i);
}

extern "C" void kernelEntry(void *multibootStruct, uint32_t magicNum) {
	printf ("hello moss\n");
	while(1);
}
