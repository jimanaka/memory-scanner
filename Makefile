###############################################################################
###          University of Hawaii, College of Engineering
### @brief   Lab 03a - memscanner - EE 491 - Spr 2022
###
### @file    Makefile
### @version 1.0 
###
### memscan - Scans /proc/self/maps, prints the mapped memory regions, and counts the number of 'A's in the mapped memory region. 
###
### @author  Jake Imanaka	<jimanaka@hawaii.edu>
### @date    08_01_2022
###
### @see     https://www.gnu.org/software/make/manual/make.html
###############################################################################

CC			= gcc
CFLAGS	= -g -Wall -I ./headers/
TARGET	= memscan
OBJFILES	= memscan.o parse-file.o bounded-memory-scan.o
HEADERS 	= headers/memscan.h headers/parse-file.h headers/bounded-memory-scan.h

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES)

memscan.o: src/memscan.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o memscan.o src/memscan.c

parse-file.o: src/parse-file.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o parse-file.o src/parse-file.c

bounded-memory-scan.o: src/bounded-memory-scan.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o bounded-memory-scan.o src/bounded-memory-scan.c

test:
	@echo "testing ./memscan ..."
	./memscan
	@echo "testing complete"

clean:
	rm -f $(TARGET) *.o

