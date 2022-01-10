# MIPS Pascal Compiler

A Pascal Compiler for the MIPS Architecture. Written for Unix/GCC in C++, using lex/yacc for parsing and Perl for unit tests.

## Usage

	// COMMAND LINE OPTIONS
	warnings: -w
	optimization:	-O0 / -O1

	// COMPILING
	make first                                            (prepare folder structure)
	make -B                                               (force compiles linker)
	make                                                  (compile the program)
  
	// PROGRAM USAGE					
	perl ./tests/dotests_spim                             (run full mips test stack)
	./comp -w -O1 <./examples/fib.p0 && spim load out.s   (generate and run fibonacci)
	./comp -w -O1 <./examples/fact.p0 && spim load out.s  (generate and run factorial)
	./comp -w -O1 <./examples/exp.p0 && spim load out.s   (generate and run exponent)
  
	Output MIPS assembly file is written to out.s
  
	// EXAMPLES
	The examples allow user input during run time:
	fib.p0: one integer               -> output fib(n)
	fact.p0: one integer              -> output fact(n)
	exp.p0: one float, one integer    -> output x^n


## Structure

	./main.cc                   (source root)
	./CodeGenerator.cc|.h       (base of the assembly code generator)
	./StackFrameManager.cc|.h   (manages the stack frame entry, return and size)
	./RegisterManager.cc|.h     (manages the assembly registry reads and writes)
	./mips/*.o                  (contains all the mips specific implementations )
	./obj/*.cc|.h               (contains precompiled mips architecture files)
	./icode/*.h                 (headers for C++ intermediate code representation)
	./parser/*.h                (headers for parsing tree instructions)
	./utils/*.cc|.h             (debugging and logging implementation)
	./tests/*.p0|.p1            (pascal unit tests based on perl routine)
	./examples/*.p0             (example pascal code to compile)
