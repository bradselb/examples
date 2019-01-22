EXE = demo
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)


CFLAGS += -Wall -D_POSIX_C_SOURCE -std=c99

all : $(EXE)

$(EXE) : $(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $^ -lm

%.o : %.c
	$(CC) -c $(CFLAGS) $?

clean :
	@rm -f $(OBJECTS) $(EXE)

run :
	./$(EXE) sequences

