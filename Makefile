
## Utility program options:
RM              = rm
RMOPTS          = -f
LD              = ld

## MIC deployment variables:
# SCP_CMD          = scp 
# MIC_SERVER       = mic0
# MIC_PATH         = ~/research/

## Compiler options for each method...
## ----------
## Message Passing Interface (MPI)
MPI_ICC         = mpicc 
MPI_ICCOPTS     = -Wall -g -O2 -pthread
MPI__HOSTOPTS   = 
MPI__MICOPTS    = -mmic -D MIC_ENV=1 

## Binary path
BP	        = bin/
## List of all binaries
ALLBINARIES    := $(BP)mb_core.host $(BP)mb_core.mic

## Make batches:
all:   host  ## mic
	@echo Done!
	@echo Destination of binaries: ./$(BP)
	@echo Type: ./run [options] to execute!
host:  mb_host
mic:   mb_mic

## Build for execution on host computer...
mb_host:	mb_core.c snapshot.h
		$(MPI_ICC) $(MPI_ICCOPTS) $(MPI__HOSTOPTS) mb_core.c -lm -o $(BP)mb.host

## Build for execution on Xeon Phi Coprocessor...
mb_mic:		mb_core.c snapshot.h
		$(MPI_ICC) $(MPI_ICCOPTS) $(MPI__MICOPTS) mb_core.c -lm -o $(BP)mb.mic

pb_copy_to_mic:
# ## Commented out for now...
#		$(SCP_CMD) $(BP)*.mic $(MIC_SERVER):$(MIC_PATH)
#		$(SCP_CMD) $(BP)*.mic $(MIC_SERVER):/tmp/

##---
clean:
		$(RM) $(RMOPTS) *.o *~ $(ALLBINARIES)
## EOF
