##########
## DuckSim Build Script
##########

## Utility program options:
RM              = rm
RMOPTS          = -f

## Compiler options for each component...
## ----------
CC		= g++ 
CCOPTS		= -Wall -g -fPIC -O0
CORE_OPTS	= -pthreads -lm
MEM_OPTS	= -pthreads -lm
NOC_OPTS	= -pthreads -lm
UTIL_OPTS	= -pthreads -lm

## Source paths
CP		= src/core/
MP		= src/mem/
NP		= src/noc/
UP		= src/util/

## Source files
CORE_SRC	:= $(CP)temp.cpp
CORE_HEADERS	:= $(CORE_SRC: %.cpp = %.h)
CORE_TEST	:= $(CORE_SRC: %.cpp = %_test.cpp)
CORE_OBJ	:= $(CORE_SRC: %.cpp = %.o)

MEM_SRC		:= $(MP)temp.cpp
MEM_HEADERS	:= $(MEM_SRC: %.cpp = %.h)
MEM_TEST	:= $(MEM_SRC: %.cpp = %_test.cpp)
MEM_OBJ		:= $(MEM_SRC: %.cpp = %.o)

#Experimental concept:
#MEM_OBJ		 = $(MEM_OBJ: $(MP) = $(BP))

NOC_SRC		:= $(NP)flit.cpp $(NP)buffer.cpp $(NP)port.cpp
NOC_HEADERS	:= $(NP)flit.h $(NP)buffer.h $(NP)port.h
NOC_TEST	:= $(NP)flit_test.cpp $(NP)buffer_test.cpp $(NP)port_test.cpp

UTIL_SRC	:= $(UP)temp.cpp
UTIL_HEADERS	:= $(UP)temp.h
UTIL_TEST	:= $(UP)temp_test.cpp

## Binary path
BP	        = bin/
## List of all binaries
CORE_OBJ	:= $(BP)core.o
MEM_OBJ		:= $(BP)mem.o
NOC_OBJ		:= $(BP)noc.o
UTIL_OBJ	:= $(BP)util.o

FINAL_OUTPUT	:= $(BP)ducksim

ALL_OBJECTS	:= $(CORE_OBJ) $(MEM_OBJ) $(NOC_OBJ) $(UTIL_OBJ)
ALL_BINARIES	:= $(FINAL_OUTPUT) 

##########

all:		ducksim
		@echo Done!
		@echo Destination of binaries: ./$(BP)

ducksim:  	core mem noc util
		$(CC) $(CCOPTS) $(CORE_OBJ) $(MEM_OBJ) $(NOC_OBJ) $(UTIL_OBJ) -o $(FINAL_OUTPUT)

core:		$(CORE_SRC) $(CORE_HEADERS) $(CORE_TEST)
		$(CC) $(CCOPTS) $(CORE_SRC) $(CORE_OPTS) -c -o $(CORE_OBJ)

mem:		$(MEM_SRC) $(MEM_HEADERS) $(MEM_TEST)
		$(CC) $(CCOPTS) $(MEM_SRC) $(MEM_OPTS) -c -o $(MEM_OBJ)

noc:		$(NOC_SRC) $(NOC_HEADERS) $(NOC_TEST)
		$(CC) $(CCOPTS) $(NOC_SRC) $(NOC_OPTS) -c -o $(NOC_OBJ)

util:		$(UTIL_SRC) $(UTIL_HEADERS) $(UTIL_TEST)
		$(CC) $(CCOPTS) $(UTIL_SRC) $(UTIL_OPTS) -c -o $(UTIL_OBJ)

clean:
		$(RM) $(RMOPTS) $(CP)*~ $(MP)*~ $(NP)*~ $(UP)*~ $(ALL_BINARIES) $(ALL_OBJECTS)

##########

## EOF
