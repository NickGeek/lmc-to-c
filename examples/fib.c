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
#define loop 12
#define end 25
#define x 28
#define y 29
#define z 30
#define lmt 31
#define one 32
#define newline 33

// LMC Memory
int memory[MEMORY_SIZE] = {
	INP,
	STA+x,
	INP,
	STA+y,
	INP,
	STA+lmt,
	LDA+newline,
	OST,
	LDA+x,
	OUT,
	LDA+y,
	OUT,
	LDA+lmt,
	BRZ+end,
	SUB+one,
	STA+lmt,
	LDA+x,
	ADD+y,
	STA+z,
	OUT,
	LDA+y,
	STA+x,
	LDA+z,
	STA+y,
	BRA+loop,
	LDA+z,
	SUB+z,
	HLT,
	DAT,
	DAT,
	DAT,
	DAT,
	DAT+1,
	DAT+10,
};

// Clean Data
#undef loop
#undef end
#undef x
#undef y
#undef z
#undef lmt
#undef one
#undef newline

// Clean Instructions
#undef HLT
#undef ADD
#undef SUB
#undef STA
#undef STO
#undef LDA
#undef BRA
#undef BRZ
#undef BRP
#undef INP
#undef OUT
#undef DAT
#undef DBG
#undef IST
#undef OST

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
			scanf("%c", &cpuRegister);
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
int runInstruction() {
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

