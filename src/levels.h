#ifndef __LEVELS_H__
#define __LEVELS_H__

#include "init.h"
#include "utils.h"
#include "screen.h"
#include "keyboard.h"

#define LEVEL_01_INTRODUCTION_TEXT "Fase 1: resolvendo problemas de carangueijo"
#define LEVEL_02_INTRODUCTION_TEXT "Fase 2: capturando Herbert"

#define PARALLAX_SIZE 3

extern unsigned int actualScreen;

typedef struct {
    float   x, y,
            velX, velY;
    int width, height;

    ALLEGRO_BITMAP *image;
} Background;

void init_background(Background *b);
void update_background(Background *b);
void draw_background(Background *b);
void destroy_background(Background *b);

void init_select_level(ALLEGRO_BITMAP **temp, ALLEGRO_BITMAP **temp2);
void update_select_level(unsigned char *key, bool *finished, 
                        unsigned char choose,
                        Player *player,
                        Background *background);
void draw_select_level( ALLEGRO_FONT* font, 
                        ALLEGRO_FONT* bold,
                        Background *b, 
                        ALLEGRO_BITMAP *title,
                        unsigned char choose);

void init_level_one(Player *player, Background *b);

void loading_screen();
void switch_level(unsigned int l, Player *player, Background *b);

#endif // __LEVELS_H__