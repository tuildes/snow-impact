#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "auxiliar.h"

#define PLAYER_DEFAULT_SPEED 10

typedef struct {
    float x, y, speed;
    unsigned int lifes:2;
    ALLEGRO_BITMAP *sprite, *lifeSpr;
} Player;

Player create_player(float x, float y);

void movement_player(Player *p, float x, float y);

void draw_player(Player p);

void destroy_player(Player *p);

#endif // __PLAYER_H__