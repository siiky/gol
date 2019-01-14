CC := musl-gcc
#CC := cc
EXEC := gol
INCLUDE := -I/usr/local/include/
HEADERS :=

SRC := \
    gol.c  \
    main.c \

OBJS := $(SRC:.c=.o)

OPT := -Og -g

CFLAGS := \
    $(INCLUDE)   \
    $(OPT)       \
    -Wall        \
    -Wconversion \
    -Wextra      \
    -flto        \
    -pedantic    \
    -static      \
    -std=c18     \

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

strip: $(EXEC)
	strip -s $(EXEC)

clean:
	$(RM) $(OBJS) $(EXEC)

check: $(SRC) $(HEADERS)
	cppcheck --std=c11 -f --language=c --enable=all $(INCLUDE) $(SRC) $(HEADERS)

tags: $(SRC) $(HEADERS)
	ctags --language-force=c --tag-relative=yes -f .tags $(SRC) $(HEADERS)

.PHONY: all check clean strip tags
