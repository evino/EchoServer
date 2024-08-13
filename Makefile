CC = gcc
CFLAGS = -Wall -Werror -Wpedantic -g
# Source Files
SRC = client.c server.c
# Object Files
OBJS = $(SRC:.c=.o)
SERVER_OBJS = server.o
CLIENT_OBJS = client.o

# Client target
# CLIENT = QueueClient


all: client server

client: $(OBJS)
	$(CC) $(CFLAGS) -o client client.o

server: $(OBJS)
	$(CC) $(CFLAGS) -o server server.o


client.o: client.c
	$(CC) $(CFLAGS) -c 	client.c


server.o: server.c
	$(CC) $(CFLAGS) -c server.c
	

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(all) $(OBJS) client server