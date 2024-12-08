
# CXX Make variable for compiler
CC=g++
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb
CCFLAGS=-std=c++11 -Wall -g3 -c #-Wno-deprecated-declarations


# object files
OBJS = Consumer.o Producer.o main.o log.o

# Program name
PROGRAM = fooddelivery

# The program depends upon its object files
$(PROGRAM) : $(OBJS)
	$(CC) -pthread -o $(PROGRAM) $(OBJS)

main.o : main.cpp
	$(CC) $(CCFLAGS) main.cpp

Producer.o : Producer.cpp Producer.h
	$(CC) $(CCFLAGS) Producer.cpp

Consumer.o: Consumer.cpp Consumer.h
	$(CC) $(CCFLAGS) Consumer.cpp

log.o: log.cpp log.h
	$(CC) $(CCFLAGS) log.cpp

clean :
	rm -f *.o *~ $(PROGRAM)
