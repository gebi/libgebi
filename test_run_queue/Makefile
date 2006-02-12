CXX = g++-4.0
CC = $(CXX)
LD = $(CXX)

#CPPFLAGS = -pipe -Wall -O2 -g3
CPPFLAGS = -I'../' -DTEST_COMPILE -pipe -Wall -O3 -s -DNDEBUG -funroll-loops -floop-optimize -march=i686 -mtune=i686 -ansi -pedantic
#LDFLAGS = -s

SUBDIRS=$(patsubst %/Makefile,%,$(wildcard */Makefile))
.PHONY: default clean $(SUBDIRS)

%.so : %.cpp ;
	$(CC) -shared $*.cpp $(CPPFLAGS) $(LDFLAGS) -o $*.so

PROGS = main_obj main_ptr
default: $(SUBDIRS) $(PROGS)

clean: $(SUBDIRS)
	rm -f $(PROGS) *~ *.o *.so

#main: $(patsubst %.cpp,%.o,$(wildcard *.cpp))

main_obj: main_obj.cpp
	$(CC) main_obj.cpp $(CPPFLAGS) $(LDFLAGS) -o main_obj

main_ptr: main_ptr.cpp
	$(CC) main_ptr.cpp $(CPPFLAGS) $(LDFLAGS) -o main_ptr

bench: default
	zsh -c 'time ./main_mutex_on >/dev/null'
	zsh -c 'time ./main_mutex_off >/dev/null'
	zsh -c 'time ./main_rwlock_on >/dev/null'
	zsh -c 'time ./main_rwlock_off >/dev/null'
	zsh -c 'time ./main_simple'

#$(wildcard *.o): $(wildcard *.h ../simple-module/*.h)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

