#Generic makefile for simple programs
CC = g++ #set C++ compiler
CFLAGS =-I$(IDIR)
IDIR = ../inc
LDIR = ../lib
ODIR = obj

LIBS= 

_DEPS = account.hpp transaction.hpp stock.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o account.o transaction.o stock.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#Rule for all files of .o extension (compile using relevant .c file and dependencies.)
$(ODIR)/%.o: %.cpp $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

#Targets for compiling files into object files into single executable.
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

exec: main
		./main

run: main exec

.PHONY:	clean

clean:	
		rm -rf $(ODIR)/*.o *~ core $(IDIR)/*~
