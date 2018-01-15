
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
