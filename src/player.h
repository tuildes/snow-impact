#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "auxiliar.h"

#define PLAYER_SPRITES_NUM 1
#define PLAYER_DEFAULT_SPEED 10

#define X_SCREEN 960 // 16 * 60
#define Y_SCREEN 540 // 9 * 60

typedef struct {
    float x, y, speed;
    ALLEGRO_BITMAP* sprite[PLAYER_SPRITES_NUM];
} Player;

Player create_player(float x, float y);

void movement_player(Player *p, float x, float y);

void draw_player(Player p);

void destroy_player(Player p);

#endif // __PLAYER_H__