# LMC to C
This program generates C code from [LMC assembly](http://www.vivaxsolutions.com/web/lmc.aspx). The script reads from stdin so you can run it and just start typing assembly, and leave a newline to generate the C code, or pipe in a script. Using shell magic you can even convert, compile, and run in one line:

```bash
cat fib.asm | python3 parser.py | gcc -xc -; ./a.out
```

You can also specify a memory size as a command line argument to `parser.py` like: `python3 parser.py 500` to have 500 cells of memory instead of the default 100.

## Extra Instructions
| Instruction | Op Code | Description                                                                                 |
| ----------- | ------- | ------------------------------------------------------------------------------------------- |
| `DBG`       | 401     | Prints the current value in the register, the program counter value, and the data in memory |
| `IST`       | 903     | Like `INP` but it accepts a character as input rather than a number                         |
| `OST`       | 904     | Outputs the current value in memory as a character instead of a number                      |