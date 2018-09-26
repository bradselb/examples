EXE = demo
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)


CFLAGS += -Wall -O2 -D_GNU_SOURCE

all : $(EXE)

$(EXE) : $(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $^ 

%.o : %.c
	$(CC) -c $(CFLAGS) $?

clean :
	@rm -f $(OBJECTS) $(EXE)
