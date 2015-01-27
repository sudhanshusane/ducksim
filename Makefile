
## Utility program options:
RM              = rm
RMOPTS          = -f

## Compiler options for each method...
## ----------
## Message Passing Interface (MPI)
CC		= g++ 
CCOPTS		= -Wall -g -O2 -pthread
LD		= ld
LDOPTS		= 

## Source paths
CP		= src/core/
MP		= src/mem/
NP		= src/noc/
## Source files
CORE_SRC	:= $(CP)temp.cpp
CORE_HEADERS	:= $(CP)temp.h
CORE_TEST	:= $(CP)test_test.cpp
MEM_SRC		:= $(MP)temp.cpp
MEM_HEADERS	:= $(MP)temp.h
MEM_TEST	:= $(MP)temp_test.cpp
NOC_SRC		:= $(NP)flit.cpp $(NP)buffer.cpp $(NP)port.cpp
NOC_HEADERS	:= $(NP)flit.h $(NP)buffer.h $(NP)port.h
NOC_TEST	:= $(NP)flit_test.cpp $(NP)buffer_test.cpp $(NP)port_test.cpp

## Binary path
BP	        = bin/
## List of all binaries
CORE_OBJ	:= $(BP)core.o
MEM_OBJ		:= $(BP)mem.o
NOC_OBJ		:= $(BP)noc.o
FINAL_OUTPUT	:= $(BP)ducksim
ALL_OBJECTS	:= $(CORE_OBJ) $(MEM_OBJ) $(NOC_OBJ)
ALL_BINARIES	:= $(FINAL_OUTPUT) 

## Make recipes
all:		ducksim
		@echo Done!
		@echo Destination of binaries: ./$(BP)

ducksim:  	core mem noc
		$(LD) $(LDOPTS)	$(CORE_OBJ) $(MEM_OBJ) $(NOC_OBJ) -o $(FINAL_OUTPUT)

core:		$(CORE_SRC) $(CORE_HEADERS) $(CORE_TEST)
		$(CC) $(CCOPTS) $(CORE_SRC) -o $(CORE_OBJ)

mem:		$(MEM_SRC) $(MEM_HEADERS) $(MEM_TEST)
		$(CC) $(CCOPTS) $(MEM_SRC) -o $(MEM_OBJ)

noc:		$(NOC_SRC) $(NOC_HEADERS) $(NOC_TEST)
		$(CC) $(CCOPTS) $(NOC_SRC) -o $(NOC_OBJ)

##---
clean:
		$(RM) $(RMOPTS) *.o *~ $(ALL_BINARIES) $(ALL_OBJECTS)
## EOF
