CXX = g++
CC = $(CXX)
LD = $(CXX)

#CPPFLAGS = -pipe -Wall -O2 -g3
CPPFLAGS = -I'../' -DTEST_COMPILE -pipe -Wall -O3 -s -DNDEBUG -funroll-loops -floop-optimize -ansi -pedantic
#LDFLAGS = -s

SUBDIRS=$(patsubst %/Makefile,%,$(wildcard */Makefile))
.PHONY: default clean $(SUBDIRS)

%.so : %.cpp ;
	$(CC) -shared $*.cpp $(CPPFLAGS) $(LDFLAGS) -o $*.so

PROGS = main_mutex_on main_mutex_off main_rwlock_on main_rwlock_off main_simple
default: $(SUBDIRS) $(PROGS)

clean: $(SUBDIRS)
	rm -f $(PROGS) *~ *.o *.so

#main: $(patsubst %.cpp,%.o,$(wildcard *.cpp))

main_mutex_on: main_mutex.cpp
	$(CC) main_mutex.cpp $(CPPFLAGS) $(LDFLAGS) -lpthread -D_MT_SUPPORT_ -o main_mutex_on

main_mutex_off: main_mutex.cpp
	$(CC) main_mutex.cpp $(CPPFLAGS) $(LDFLAGS) -o main_mutex_off

main_rwlock_on: main_rwlock.cpp
	$(CC) main_rwlock.cpp $(CPPFLAGS) $(LDFLAGS) -lpthread -D_MT_SUPPORT_ -o main_rwlock_on

main_rwlock_off: main_rwlock.cpp 
	$(CC) main_rwlock.cpp $(CPPFLAGS) $(LDFLAGS) -o main_rwlock_off

main_simple: main_simple.cpp

bench: default
	zsh -c 'time ./main_mutex_on >/dev/null'
	zsh -c 'time ./main_mutex_off >/dev/null'
	zsh -c 'time ./main_rwlock_on >/dev/null'
	zsh -c 'time ./main_rwlock_off >/dev/null'
	zsh -c 'time ./main_simple'

#$(wildcard *.o): $(wildcard *.h ../simple-module/*.h)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

