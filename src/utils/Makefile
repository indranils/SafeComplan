CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall

all: primitive.o readinputs.o writeconstraints.o extractoutput.o generatetrajectory.o

primitive.o : primitive.h primitive.cpp
	$(CC) $(CFLAGS) primitive.cpp

readinputs.o : primitive.h readinputs.h readinputs.cpp
	$(CC) $(CFLAGS) readinputs.cpp

writeconstraints.o : primitive.h readinputs.h writeconstraints.h writeconstraints.cpp
	$(CC) $(CFLAGS) writeconstraints.cpp

generatetrajectory.o : primitive.h readinputs.h generatetrajectory.cpp
	$(CC) $(CFLAGS) generatetrajectory.cpp

extractOutput.o : extractoutput.h extractoutput.cpp
	$(CC) $(CFLAGS) extractoutput.cpp


.PHONY: clean
clean : 
	rm -f *.o

