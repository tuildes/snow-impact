#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "init.h"

// Variaveis de ambiente
#define PLAYER_DEFAULT_SPEED 3

// Sprites do jogador
#define PLAYER_W 24
#define PLAYER_H 56

typedef struct {
    float x, y, speed;
    unsigned int lifes:2;
    long invincibility;
    double time;
    unsigned int kills;
    ALLEGRO_BITMAP *sprite;
} Player;

Player create_player(float x, float y);

void update_player(Player *player, unsigned char *key, ALLEGRO_SAMPLE* sample_shot);

void draw_player(Player player);

void destroy_player(Player *p);

void damage_player(Player *player);

bool collide(float ax1, float ay1, float ax2, float ay2,
             float bx1, float by1, float bx2, float by2);

#endif // __PLAYER_H__