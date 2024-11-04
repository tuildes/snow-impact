#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "auxiliar.h"

// Variaveis de ambiente
#define PLAYER_DEFAULT_SPEED 3

// Sprites do jogador
#define PLAYER_W 24
#define PLAYER_H 56

// Colisoes de tela
#define LEFT_COLLISION 0
#define RIGHT_COLISSION (BUFFER_W - PLAYER_W)
#define UP_COLLISION 0
#define DOWN_COLLISION (BUFFER_H - BUFFER_STATUS_H - PLAYER_H)

typedef struct {
    float x, y, speed;
    unsigned int lifes:2;
    ALLEGRO_BITMAP *sprite, *lifeSpr;
} Player;

Player create_player(float x, float y);

void update_player(Player *player, unsigned char *key, ALLEGRO_SAMPLE* sample_shot);

void destroy_player(Player *p);

#endif // __PLAYER_H__