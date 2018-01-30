CC=musl-gcc
# `/usr/local/include/` for `utils/ifjmp.h`
CFLAGS=-Wall -Wextra -Wconversion -O3 -I/usr/local/include/
EXEC=gol
SRC=main.c gol.c
OBJS=$(SRC:.c=.o)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

clean:
	rm -f $(EXEC) $(OBJS)

test: $(EXEC)
	./$(EXEC) | less
