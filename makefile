# Makefile to LBP IMAGE COMPARATION

OBJS	= src/main.c
SOURCE	= src/main.c
# HEADER	= 
OUT	= SPACE_IMPACT
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -Werror -Wpedantic -Walloc-zero -Wconversion -Wduplicated-branches -Wduplicated-cond -Wformat=2 -Wshadow
LFLAGS	 = -lm
LDFLAGS = -lallegro -lallegro_font

all: SPACE_IMPACT

SPACE_IMPACT: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(LDFLAGS)

src/main.o: src/main.c
	$(CC) $(FLAGS) src/main.c -o src/main.o

clean:
	rm -f $(OBJS) $(OUT)

valgrind: SPACE_IMPACT
	valgrind ./SPACE_IMPACT

valgrind_leakcheck: ./LBP
	valgrind --leak-check=full ./SPACE_IMPACT

valgrind_extreme: LBP
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes ./SPACE_IMPACT