import sys
import itertools
import re
import os

memory = []
labels = []

__location__ = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))
start = open(os.path.join(__location__, "template", "start.c"), "r").read()
end = open(os.path.join(__location__, "template", "end.c"), "r").read()

instructions = {
	'HLT',
	'ADD',
	'SUB',
	'STA',
	'STO',
	'LDA',
	'BRA',
	'BRZ',
	'BRP',
	'INP',
	'OUT',
	'DAT',
	'DBG',
	'IST',
	'OST'
}

# Get output
lines = [
	re.compile("\\s+").split(line.strip())
	for line in list(itertools.takewhile(lambda line: len(line.strip()) > 0, sys.stdin))
]

instructionCounter = 0;
lineCounter = 0;
for line in lines:
	lineCounter += 1

	if line[0][:2] == "//":
		continue
	elif len(line) == 1:
		# Simple command
		memory.append(line[0])
	elif len(line) == 2 and line[0] in instructions:
		# Command with memory location
		memory.append(line[0] + "+" + line[1])
	elif len(line) >= 2 and len(line) <= 3:
		# Command with label
		if len(line) == 3:
			memory.append(line[1] + "+" + line[2])
		else:
			memory.append(line[1])
		labels.append((line[0], instructionCounter))
	else:
		print("Compilation error on line " + str(lineCounter), file=sys.stderr)
		sys.exit(0)

	instructionCounter += 1

memorySize = 100 if len(sys.argv) <= 1 else int(sys.argv[1])

output = """// LMC Memory Size
#define MEMORY_SIZE {size}

{start}
// LMC Data Def""".format(size=memorySize, start=start)

for label in labels:
	output += "\n#define {0} {1}".format(label[0], label[1])

output += """\n
// LMC Memory
int memory[MEMORY_SIZE] = {"""

for instruction in memory:
	output += "\n\t" + instruction + ","

output += """
};

// Clean Data"""

for label in labels:
	output += "\n#undef " + label[0]

output += "\n" + end

print(output)
