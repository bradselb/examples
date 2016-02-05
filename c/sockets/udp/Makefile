SERVER = udpserver
CLIENT = udpclient

CFLAGS += -Wall -O2 -std=c99

all : $(SERVER) $(CLIENT)

$(SERVER): $(SERVER).c
	$(CC) -o $@  $^

$(CLIENT): $(CLIENT).c
	$(CC) -o $@  $^

clean :
	@rm -f $(SERVER) $(CLIENT)
