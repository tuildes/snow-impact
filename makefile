# Makefile to LBP IMAGE COMPARATION

OBJS	= src/core.o src/init.o src/boss.o src/player.o src/screen.o src/bullet.o src/keyboard.o src/levels.o src/enemie.o
SOURCE	= src/core.c src/init.c src/boss.o src/player.c src/screen.c src/bullet.c src/keyboard.c src/levels.c src/enemie.c
HEADER	= src/init.h src/boss.o src/screen.h src/player.h src/bullet.h src/keyboard.h src/levels.h src/levels.h src/enemie.h
OUT	= SNOW_IMPACT
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -Werror -Wpedantic -Walloc-zero -Wconversion -Wduplicated-branches -Wduplicated-cond -Wformat=2 -Wshadow
LFLAGS	 = -lm
LDFLAGS = -lallegro -lallegro_font -lallegro_image -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_primitives

all: SNOW_IMPACT

SNOW_IMPACT: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(LDFLAGS)

src/core.o: src/core.c
	$(CC) $(FLAGS) src/core.c -o src/core.o

src/init.o: src/init.c
	$(CC) $(FLAGS) src/init.c -o src/init.o

src/boss.o: src/boss.c
	$(CC) $(FLAGS) src/boss.c -o src/boss.o

src/player.o: src/player.c
	$(CC) $(FLAGS) src/player.c -o src/player.o

src/bullet.o: src/bullet.c
	$(CC) $(FLAGS) src/bullet.c -o src/bullet.o

src/enemie.o: src/enemie.c
	$(CC) $(FLAGS) src/enemie.c -o src/enemie.o

src/keyboard.o: src/keyboard.c
	$(CC) $(FLAGS) src/keyboard.c -o src/keyboard.o

src/levels.o: src/levels.c
	$(CC) $(FLAGS) src/levels.c -o src/levels.o

src/screen.o: src/screen.c
	$(CC) $(FLAGS) src/screen.c -o src/screen.o

clean:
	rm -f $(OBJS) $(OUT)

valgrind: SNOW_IMPACT
	valgrind ./SNOW_IMPACT

valgrind_leakcheck: SNOW_IMPACT
	valgrind --leak-check=full ./SNOW_IMPACT

valgrind_extreme: SNOW_IMPACT
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes ./SNOW_IMPACT