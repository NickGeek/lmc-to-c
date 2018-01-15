// LMC Memory Size
#define MEMORY_SIZE 100

// LMC Instruction Def
#define HLT 0
#define ADD (1 * MEMORY_SIZE)
#define SUB (2 * MEMORY_SIZE)
#define STA (3 * MEMORY_SIZE)
#define STO (3 * MEMORY_SIZE)
#define LDA (5 * MEMORY_SIZE)
#define BRA (6 * MEMORY_SIZE)
#define BRZ (7 * MEMORY_SIZE)
#define BRP (8 * MEMORY_SIZE)
#define INP (9 * MEMORY_SIZE) + 1
#define OUT (9 * MEMORY_SIZE) + 2
#define DAT 0

// Implementation Instructions (not standard)
#define DBG (4 * MEMORY_SIZE) + 1
#define IST (9 * MEMORY_SIZE) + 3
#define OST (9 * MEMORY_SIZE) + 4

// LMC Data Def
#define H 26
#define e 27
#define l 28
#define o 29
#define SPACE 30
#define W 31
#define r 32
#define d 33
#define NEWLINE 34

// LMC Memory
int memory[MEMORY_SIZE] = {
	LDA+H,
	OST,
	LDA+e,
	OST,
	LDA+l,
	OST,
	LDA+l,
	OST,
	LDA+o,
	OST,
	LDA+SPACE,
	OST,
	LDA+W,
	OST,
	LDA+o,
	OST,
	LDA+r,
	OST,
	LDA+l,
	OST,
	LDA+d,
	OST,
	LDA+NEWLINE,
	OST,
	DBG,
	HLT,
	DAT+72,
	DAT+101,
	DAT+108,
	DAT+111,
	DAT+32,
	DAT+119,
	DAT+114,
	DAT+100,
	DAT+10,
};

// Clean Data
#undef H
#undef e
#undef l
#undef o
#undef SPACE
#undef W
#undef r
#undef d
#undef NEWLINE

// C Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LMC CPU Cache/Register
int cpuRegister = 0;
int counter = 0;

// LMC Operations in C
void halt(int cell) {
	exit(0);
}

void add(int cell) {
	cpuRegister += memory[cell];
}

void subtract(int cell) {
	cpuRegister -= memory[cell];
}

void store(int cell) {
	memory[cell] = cpuRegister;
}

void load(int cell) {
	cpuRegister = memory[cell];
}

void branch(int cell) {
	counter = cell - 1;
}

void branchIfZero(int cell) {
	if (cpuRegister == 0) branch(cell);
}

void branchIfPositive(int cell) {
	if (cpuRegister >= 0) branch(cell);
}

void io(int cmd) {
	char input;

	switch (cmd) {
		case 1:
			// Input
			scanf("%i", &cpuRegister);
			break;

		case 2:
			// Output
			printf("%d\n", cpuRegister);
			break;

		case 3:
			// String Input
			scanf("%c", &input);
			cpuRegister = (int)input;
			break;

		case 4:
			// String Output
			printf("%c", cpuRegister);
			break;
	}
}

void drawSeperator() {
	printf("\n=====================================\n");
}

void debug(int cmd) {
	drawSeperator();
	printf("Program Counter: %d\n", counter);
	printf("Register Value: %d\n", cpuRegister);

	printf("Memory:\n[");
	for (int i = 0; i < MEMORY_SIZE; i++) {
		char seperator[] = ", ";
		if (i == MEMORY_SIZE - 1) strcpy(seperator, "");

		printf("%d%s", memory[i], seperator);
	}
	printf("]\n");
	drawSeperator();
}

void (*functions[10]) (int cell) = {
	[0] = halt,
	[1] = add,
	[2] = subtract,
	[3] = store,
	[4] = debug,
	[5] = load,
	[6] = branch,
	[7] = branchIfZero,
	[8] = branchIfPositive,
	[9] = io
};

// Run Program
void runInstruction() {
	int cell = memory[counter];

	// Decode Instruction
	int instruction = cell/MEMORY_SIZE % 10;
	int address = cell - (instruction * MEMORY_SIZE);

	// Run instruction
	(*functions[instruction])(address);
}

int main() {
	while (1) {
		runInstruction();
		counter++;
	}
	return 0;
}

