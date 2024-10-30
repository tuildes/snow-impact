#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "auxiliar.h"

#define PLAYER_SPRITES_NUM 1

typedef struct {
    float x, y, speed;
    ALLEGRO_BITMAP* sprite[PLAYER_SPRITES_NUM];
} Player;

Player create_player(float x, float y, float speed);

void movement_player(Player *p, unsigned char *orientation);

void destroy_player(Player p);

#endif // __PLAYER_H__