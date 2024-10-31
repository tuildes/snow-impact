# Makefile to LBP IMAGE COMPARATION

OBJS	= src/main.o src/auxiliar.o src/player.o
SOURCE	= src/main.c src/auxiliar.c src/player.c
HEADER	= src/auxiliar.h src/player.h
OUT	= SNOW_IMPACT
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -Werror -Wpedantic -Walloc-zero -Wconversion -Wduplicated-branches -Wduplicated-cond -Wformat=2 -Wshadow
LFLAGS	 = -lm
LDFLAGS = -lallegro -lallegro_font -lallegro_image -lallegro_ttf -lallegro_audio -lallegro_acodec

all: SNOW_IMPACT

SNOW_IMPACT: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(LDFLAGS)

src/main.o: src/main.c
	$(CC) $(FLAGS) src/main.c -o src/main.o

src/auxiliar.o: src/auxiliar.c
	$(CC) $(FLAGS) src/auxiliar.c -o src/auxiliar.o

src/player.o: src/player.c
	$(CC) $(FLAGS) src/player.c -o src/player.o

clean:
	rm -f $(OBJS) $(OUT)

valgrind: SNOW_IMPACT
	valgrind ./SNOW_IMPACT

valgrind_leakcheck: SNOW_IMPACT
	valgrind --leak-check=full ./SNOW_IMPACT

valgrind_extreme: SNOW_IMPACT
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes ./SNOW_IMPACT