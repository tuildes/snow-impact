#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "utils.h"
#include "init.h"

// Variaveis de ambiente
#define PLAYER_DEFAULT_SPEED 3

// Sprites do jogador
#define PLAYER_W 24
#define PLAYER_H 56

typedef struct {
    float x, y, speed;
    unsigned int lifes:2;
    double time;
    ALLEGRO_BITMAP *sprite;
} Player;

Player create_player(float x, float y);

void update_player(Player *player, unsigned char *key, ALLEGRO_SAMPLE* sample_shot);

void destroy_player(Player *p);

void draw_player(Player player);

#endif // __PLAYER_H__