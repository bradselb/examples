SHELL=/bin/bash


TARGET = arm-linux
PREFIX = ${HOME}/buildroot/output/host/usr/bin/

CC = ${PREFIX}/${TARGET}-gcc

EXE = hello
SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)
CFLAGS += -Wall -O2 -std=gnu99


all : $(EXE)

$(EXE) : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

%.o : %.cpp
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(EXE)

readelf:$(EXE)
	readelf -hd $(EXE)
