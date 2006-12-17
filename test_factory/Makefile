CXX = g++
CC = $(CXX)
LD = $(CXX)

#CPPFLAGS = -pipe -Wall -O3 -s -DNDEBUG -ansi -pedantic
CPPFLAGS = -I'../' -DTEST_COMPILE -pipe -Wall -O3 -s -DNDEBUG -funroll-loops -floop-optimize -ansi -pedantic
LDFLAGS =

SUBDIRS=$(patsubst %/Makefile,%,$(wildcard */Makefile))
.PHONY: default clean $(SUBDIRS)

%.so : %.cpp ;
	$(CC) -shared $*.cpp $(CPPFLAGS) $(LDFLAGS) -o $*.so

default: $(SUBDIRS) main

clean: $(SUBDIRS)
	rm -f main *~ *.o *.so

#main: $(patsubst %.cpp,%.o,$(wildcard *.cpp))

main: main.cpp
	$(CC) main.cpp $(CPPFLAGS) $(LDFLAGS) -lpthread -o main

#$(wildcard *.o): $(wildcard *.h ../simple-module/*.h)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

