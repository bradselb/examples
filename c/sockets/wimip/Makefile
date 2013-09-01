EXE = client

SOURCES = $(wildcard *.c)
OBJS := $(SOURCES:%.c=%.o)

CFLAGS += -Wall -O2 -std=gnu99 -I../lib

all : $(EXE)

run : $(EXE)
	./client --host checkip.dyn.com --port http

$(EXE) : $(OBJS)
	$(CC) -o $@  $^

%.o : %.c
	$(CC) -c $(CFLAGS) $<

clean :
	@rm -f $(OBJS) $(EXE)  
