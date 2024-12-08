# CXX Make variable for compiler
CC=g++
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb
CCFLAGS=-std=c++11 -Wall -g3 -c

# object files
OBJS = Consumer.o Producer.o main.o log.o

# Program name
PROGRAM = fooddelivery

# The program depends upon its object files
$(PROGRAM) : $(OBJS)
	$(CC) -pthread -o $(PROGRAM) $(OBJS)

main.o : src/main.cpp
	$(CC) $(CCFLAGS) src/main.cpp

Producer.o : src/Producer.cpp include/Producer.h
	$(CC) $(CCFLAGS) src/Producer.cpp

Consumer.o: src/Consumer.cpp include/Consumer.h
	$(CC) $(CCFLAGS) src/Consumer.cpp

log.o: src/log.cpp include/log.h
	$(CC) $(CCFLAGS) src/log.cpp

clean :
	rm -f *.o *~ $(PROGRAM)
