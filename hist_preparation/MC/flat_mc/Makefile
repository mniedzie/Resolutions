# Makefile for HEP Tutorial modified

C=c++
LD=c++

ROOTCFLAGS=$(shell root-config --cflags)
ROOTLIBS=$(shell root-config --libs)

CFLAGS =
LFLAGS = 

RCXX=$(CFLAGS) $(ROOTCFLAGS)
RLXX=$(LFLAGS) $(ROOTLIBS)

SRC1= MySelector.o MyJet.o

%.o: %.C %.h
		$(C) $(RCXX) -c $<

all: Analysis

example.o: Analysis.C MySelector.h
		$(C) $(RCXX) -c $<

Analysis: $(SRC1) example.o
		$(LD) $(SRC1) Analysis.o $(RLXX) -o Analysis_excl_parallel.x
		@echo '-> Analysis.x created!'

clean:
		@rm -f *~
		@rm -f *.o
		@rm -f *.x
