CC = gcc
CFLAGS = -Wall -g
LIBS = -lsqlite3    

TARGET = bank

SRC = $(wildcard src/*.c) $(wildcard src/telas/*.c) main.c
OBJS = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
