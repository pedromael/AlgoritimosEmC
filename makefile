CC = gcc
CFLAGS = -Wall -g
LIBS = 

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

# Regra para verificar se o compilador e as bibliotecas estão disponíveis
check:
	@sdl2-config --version > /dev/null || (echo "SDL2 não encontrado. Instale a biblioteca SDL2." && exit 1)
