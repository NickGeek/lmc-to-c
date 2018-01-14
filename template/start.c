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
