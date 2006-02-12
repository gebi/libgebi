CXX = g++-4.0
CC = $(CXX)
LD = $(CXX)

install_ = install
name_ = libgebi-dev

etc = ${DESTDIR}/etc/
usr = ${DESTDIR}/usr
usrbin = $(usr)/bin
usrsbin = $(usr)/sbin
usrshare = $(usr)/share/$(name_)
usrdoc = $(usr)/share/doc/$(name_)
usrinc = $(usr)/include/$(name_)
man8 = $(usr)/share/man/man8/


#CPPFLAGS = -pipe -Wall -O2 -g3
#CPPFLAGS = -pipe -Wall -O3 -s -DNDEBUG -funroll-loops -floop-optimize -march=i686 -mtune=i686 -ansi -pedantic
#LDFLAGS = -s

SUBDIRS=$(patsubst %/Makefile,%,$(wildcard */Makefile))
.PHONY: default clean $(SUBDIRS)

%.so : %.cpp ;
	$(CC) -shared $*.cpp $(CPPFLAGS) $(LDFLAGS) -o $*.so

PROGS =
default: $(SUBDIRS) $(PROGS)

clean: $(SUBDIRS)
	rm -f $(PROGS) *.o *.so

#main: $(patsubst %.cpp,%.o,$(wildcard *.cpp))

#$(wildcard *.o): $(wildcard *.h ../simple-module/*.h)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

install:
	$(install_) -d -m 755 $(usr)/include/gebi
	$(install_) -m 644 *.hpp $(usr)/include/gebi
