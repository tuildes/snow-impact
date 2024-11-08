#ifndef __BULLET_H__
#define __BULLET_H__

#include "utils.h"
#include "init.h"

#include "screen.h"
#include "player.h"

typedef struct {
    bool used;
    float x, y, dx, dy;
} Bullet;

#define BULLET_SPEED (PLAYER_DEFAULT_SPEED << 1)  // Velocidade dos tiros na tela
#define BULLET_DELAY 20 // Delay entre cada tiro do jogador

#define BULLET_H 6
#define BULLET_W 12

#define SHOTS_MAX 128

extern ALLEGRO_BITMAP *bullet_sprite;
extern Bullet shots[SHOTS_MAX];
extern unsigned int newBullet;
extern unsigned int delay;

void shots_init();

bool shots_add(float x, float y, ALLEGRO_SAMPLE* sample_shot);

void shots_update();

void update_shots();

void draw_shots();

#endif // __BULLET_H__