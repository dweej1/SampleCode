# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -std=c++0x -g -Wall 

AM_CPPFLAGS = -I/usr/local/include/boost

LFLAGS = -L/usr/local/lib

LIBS = -lboost_regex -lboost_system -lboost_thread

SRCS = index_gen.cc BookIndex.cc CommonWordHash.cc BookIndexHash.cc BookIndexRBTree.cc BookIndexMapReduce.cc BookIndexFactory.cc 

OBJS = $(SRCS:.cc=.o)

MAIN = index_gen

.PHONY: depend clean

all:    $(MAIN)
	@echo building your code!

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cc.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean-local:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
