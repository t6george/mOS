void printf(const char *s) {
	unsigned short* stdout = (unsigned short*) 0xb8000;
	for (int i = 0; *(s+i) != '\0'; ++i)
		*stdout = (*stdout & 0xFF00) | *(s+i);
}

extern "C" void kernelEntry(void *multibootStruct, unsigned int magicNum) {
	printf ("hello from mOS\n");
	while(1);
}
