
CC = gcc
CFLAGS = -c -std=c99 -g
LDFLAGS = -g
SRC = $(wildcard src/*.c)
HDR = $(wildcard include/*.h)
OBJ = $(SRC:src/%.c=src/%.o)
EXEC = Vnmtest

# Reglas
all: ${EXEC}

${EXEC}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

src/%.o: src/%.c ${HDR}
	${CC} ${CFLAGS} $< -o $@

clean:
	rm -f src/*.o ${EXEC}
