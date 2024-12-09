#ifndef __LEVELS_H__
#define __LEVELS_H__

#include "init.h"
#include "screen.h"
#include "keyboard.h"
#include "enemy.h"
#include "structs.h"

#include <math.h>

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
void destroy_background(Background *b);

void init_select_level(unsigned int *actualScreen);
void update_select_level(unsigned char *key, bool *finished, 
                        unsigned char choose,
                        Player *player,
                        Background *background,
                        unsigned int *actualScreen,
                        Boss *boss, 
                        Bullet *bulletsPlayer, Bullet *bulletsEnemy,
                        Enemy *enemies);
void draw_select_level( ALLEGRO_FONT* font, ALLEGRO_FONT* title,
                        Background *b, 
                        unsigned char choose);

void switch_level(unsigned int l, Player *player, Background *b, 
                  unsigned int *actualScreen, 
                  Boss *boss, 
                  Bullet *bulletsPlayer, Bullet *bulletsEnemy,
                  Enemy *enemies);

void destroy_actual_level(unsigned int actualScreen, Background *b,
                          Boss *boss, 
                          Bullet *bulletsPlayer, Bullet *bulletsEnemy,
                          Enemy *enemies);
                          
int draw_history_level(size_t max, float *y, 
                        const char *texts[], 
                        ALLEGRO_FONT *font);

void draw_stats_level(ALLEGRO_FONT* font, ALLEGRO_FONT* title, 
                      Background *b, Player player);

#endif // __LEVELS_H__