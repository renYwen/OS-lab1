#include "boot.h"

#define SECTSIZE 512

void bootMain(void) {
	//TODO
	// print a message to the console
	puts("Hello, world!");

	// read the first sector of the disk
	char buffer[SECTSIZE];
	readSect(buffer, 0);

	// print the content of the sector
	int i;
	for (i = 0; i < SECTSIZE; i ++) {
		putchar(buffer[i]);
	}

	// wait for a key press
	getchar();

	// exit the program
	exit(0);
}


void waitDisk(void) { // waiting for disk
	while((inByte(0x1F7) & 0xC0) != 0x40);
}

void readSect(void *dst, int offset) { // reading a sector of disk
	int i;
	waitDisk();
	outByte(0x1F2, 1);
	outByte(0x1F3, offset);
	outByte(0x1F4, offset >> 8);
	outByte(0x1F5, offset >> 16);
	outByte(0x1F6, (offset >> 24) | 0xE0);
	outByte(0x1F7, 0x20);

	waitDisk();
	for (i = 0; i < SECTSIZE / 4; i ++) {
		((int *)dst)[i] = inLong(0x1F0);
	}
}
