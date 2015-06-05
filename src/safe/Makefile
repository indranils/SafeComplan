CFLAGS = -Wall -c
LFLAGS = -Wall
all = tool_z3


UTILS_DIR = ../utils

OBJS_UTILS = $(UTILS_DIR)/primitive.o $(UTILS_DIR)/readinputs.o $(UTILS_DIR)/writeconstraints.o $(UTILS_DIR)/generatetrajectory.o $(UTILS_DIR)/extractoutput.o

OBJS_Z3 = $(OBJS_UTILS) writespecificationconstraints.o safeltlmotionplanning.o


CC = g++
tool_z3 : $(OBJS_Z3)
	$(CC) $(LFLAGS) $(OBJS_Z3) -o tool_z3

writespecificationconstraints.o : writespecificationconstraints.h writespecificationconstraints.cpp
	$(CC) $(CFLAGS) writespecificationconstraints.cpp

safeltlmotionplanning.o : $(UTILS_DIR)/primitive.h $(UTILS_DIR)/readinputs.h $(UTILS_DIR)/writeconstraints.h $(UTILS_DIR)/generatetrajectory.h writespecificationconstraints.h safeltlmotionplanning.cpp
	$(CC) $(CFLAGS) safeltlmotionplanning.cpp


util :
	$(MAKE) -C $(UTILS_DIR)


.PHONY: clean
clean : 
	rm -f *.o
	rm -f tool_*
	$(MAKE) -C $(UTILS_DIR) clean
