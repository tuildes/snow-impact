#ifndef __LEVELS_H__
#define __LEVELS_H__

#include "init.h"
#include "utils.h"
#include "screen.h"

#define LEVEL_01_INTRODUCTION_TEXT "Fase 1: resolvendo problemas de carangueijo"
#define LEVEL_02_INTRODUCTION_TEXT "Fase 2: capturando Herbert"

#define PARALLAX_SIZE 3

typedef struct {
    float   x, y,
            velX, velY;
    int width, height;

    ALLEGRO_BITMAP *image;
} Background;

void init_background(Background *b);

void update_background(Background *b);

void draw_background(Background *b);

void destroy_backround(Background *b);

#endif // __LEVELS_H__