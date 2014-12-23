EXE = checkSensors
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)


CFLAGS += -Wall -O2 -std=c99

all : $(EXE)

$(EXE) : $(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $^ -lm

%.o : %.c
	$(CC) -c $(CFLAGS) $?

clean :
	@rm -f $(OBJECTS) $(EXE)
