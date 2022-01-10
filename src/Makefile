
# Compiler
CC        = gcc
CXX       = g++

# Params
WARNINGS	= -Wall -ansi
OTHERS		= -m64 -g
DEFINES		= -DDEBUG
IDIRS			= -I.

# Flags
CFLAGS		= $(WARNINGS) $(OTHERS) $(DEFINES) $(IDIRS)
LFLAGS		= 
YFLAGS		= --defines --debug --verbose
LDFLAGS		= -m64 -g
LOADLIBS	= -lfl -lm

# Core object files
OBJFILES	= main.o debug.o  \
						CodeGenerator.o StackFrameManager.o RegisterManager.o \
            MCode.o MBase.o MAux.o MRegister.o MOperand.o MOperator.o MStatement.o
OBJDIR		= gen/
OBJS			= $(addprefix $(OBJDIR),$(OBJFILES))

# Precompiled object files
POBJFILES = types.o SyntaxTree.o Node.o Symbol.o SymbolTable.o Scope.o \
            IntermediateCode.o IStatement.o IOperand.o IOperator.o \
            ICGenerator0.o ICGenerator.o
POBJDIR   = obj/64/
POBJS     = $(addprefix $(POBJDIR),$(POBJFILES))

IMPORTANT	= comp.[hly] *.h *.c *.cc \
		  Makefile

.PHONY: all first clean backup dirs showdeps

all: comp

# To be executed before the very first build
first: dirs

# Lexer dependencies
comp: $(POBJDIR)y.tab.o $(POBJDIR)lex.yy.o $(OBJS) $(POBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LOADLIBS)

clean:	
	rm -f $(OBJDIR)*.o comp \
	    `find . -name core -o -name \*\.bak`

backup:
	tar cfz ../CoCo-`date +'%y%m%d-%H%M'`.tar.gz $(IMPORTANT)

dirs:
	mkdir gen

# Show dependencies between .c files
showdeps:
	$(CXX) -MM *.c *.cc

# Core dependencies
$(OBJDIR)%.o: %.c
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJDIR)%.o: %.cc
	$(CXX) $(CFLAGS) -c -o $@ $<
	
$(OBJDIR)%.o: parser/%.cc
	$(CXX) $(CFLAGS) -c -o $@ $<
	
$(OBJDIR)%.o: icode/%.cc
	$(CXX) $(CFLAGS) -c -o $@ $<
	
$(OBJDIR)%.o: mips/%.cc
	$(CXX) $(CFLAGS) -c -o $@ $<
	
$(OBJDIR)%.o: utils/%.c
	$(CXX) $(CFLAGS) -c -o $@ $<

bt: all
	gdb -x gdb.script ./comp

