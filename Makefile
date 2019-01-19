PLATFORM := PLATFORM_DESKTOP

CC := gcc

INCLUDE_PATHS := \
    -I/usr/local/include/ \

LDFLAGS := \

OPT := \
    -Og \

CFLAGS := \
    $(OPT)                    \
    -Wall                     \
    -Wextra                   \
    -Wmissing-prototypes      \
    -Wpedantic                \
    -Wstrict-prototypes       \
    -flto                     \
    -no-pie                   \
    -std=c11                  \

# Order matters, dont change
LDLIBS := \
    -lraylib   \
    -lGL       \
    -lm        \
    -lpthread  \
    -ldl       \
    -lX11      \
    -lXrandr   \
    -lXinerama \
    -lXi       \
    -lXxf86vm  \
    -lXcursor  \

CPPFLAGS := \
    -D$(PLATFORM) \

SRC := \
    bs.c   \
    gens.c \
    gol.c  \
    main.c \

OBJS := $(SRC:.c=.o)
EXE := gol

all: $(EXE)

$(EXE): $(OBJS)
	@echo "CC $< -> $@"
	@$(CC) -o $(EXE) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) $(CPPFLAGS)

%.o: %.c
	@echo "CC $< -> $@"
	@$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) $(CPPFLAGS)

clean:
	rm -f $(EXE) $(OBJS)

.PHONY: all clean
