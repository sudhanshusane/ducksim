##########
## DuckSim Build Script
##########

## Utility program options:
RM              = rm
RMOPTS          =

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
TP		= test/

## Source files
CORE_SRC	:= $(CP)*.cpp
CORE_HEADERS	:= $(CORE_SRC: %.cpp = %.h)
CORE_OBJ	:= $(CORE_SRC: %.cpp = %.o)

MEM_SRC		:= $(MP)*.cpp
MEM_HEADERS	:= $(MEM_SRC: %.cpp = %.h)
MEM_OBJ		:= $(MEM_SRC: %.cpp = %.o)

NOC_SRC		:= $(NP)*.cpp
NOC_HEADERS	:= $(NOC_SRC: %.cpp = %.h)
NOC_OBJ		:= $(NOC_SRC: %.cpp = %.o)

UTIL_SRC	:= $(UP)*.cpp
UTIL_HEADERS	:= $(UTIL_SRC: %.cpp = %.h)
UTIL_OBJ	:= $(UTIL_SRC: %.cpp = %.o)

TEST_SRC	:= $(TP)*.cpp
TEST_HEADERS	:= $(TEST_SRC: %.cpp = %.h)
TEST_OBJ	:= $(TEST_SRC: %.cpp = %.o)

## Binary path
BP	        = bin/
## List of all binaries
FINAL_OUTPUT	:= $(BP)ducksim
TEST_OUTPUT	:= $(BP)testsim

ALL_OBJECTS	:= $(CORE_OBJ) $(MEM_OBJ) $(NOC_OBJ) $(UTIL_OBJ) $(TEST_OBJ)
ALL_BINARIES	:= $(FINAL_OUTPUT) $(TEST_OUTPUT)

##########

all:		ducksim
		@echo Done!
		@echo Destination of binaries: ./$(BP)

ducksim:  	core mem noc util
		$(CC) $(CCOPTS) $(CORE_OBJ) $(MEM_OBJ) $(NOC_OBJ) $(UTIL_OBJ) -o $(FINAL_OUTPUT)

core:		$(CORE_SRC) $(CORE_HEADERS)
		$(CC) $(CCOPTS) $(CORE_OPTS) -c -- $(CORE_SRC)

mem:		$(MEM_SRC) $(MEM_HEADERS)
		$(CC) $(CCOPTS) $(MEM_OPTS) -c -- $(MEM_SRC)

noc:		$(NOC_SRC) $(NOC_HEADERS)
		$(CC) $(CCOPTS) $(NOC_OPTS) -c -- $(NOC_SRC)

util:		$(UTIL_SRC) $(UTIL_HEADERS)
		$(CC) $(CCOPTS) $(UTIL_OPTS) -c -- $(UTIL_SRC)

test:		$(TEST_SRC) $(TEST_HEADERS) \
		$(UTIL_SRC) $(UTIL_HEADERS) \
		$(CORE_SRC) $(CORE_HEADERS) \
		$(MEM_SRC) $(MEM_HEADERS)   \
		$(NOC_SRC) $(NOC_HEADERS)
		$(CC) $(CCOPTS) $(TEST_OPTS) -c -- $(TEST_SRC)
		$(CC) $(CCOPTS) -o $(TEST_OUTPUT) -- $(TEST_OBJ)

clean:
		$(RM) $(RMOPTS) -- $(CP)*~ $(MP)*~ $(NP)*~ $(UP)*~ $(TP)*~ $(ALL_BINARIES)

##########

## EOF
