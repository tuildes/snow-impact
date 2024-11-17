#ifndef __BULLET_H__
#define __BULLET_H__

#include "utils.h"
#include "init.h"

#include "screen.h"
#include "player.h"
#include "enemie.h"

typedef struct {
    bool used;
    bool enemy;
    size_t sprite;
    float x, y, dx, dy;
} Bullet;

typedef struct {
    bool actived;
    bool get;
    float time;
    float x, y, dx, width, height;
    unsigned int sprite:1;
} Special;

#define BULLET_SPEED (PLAYER_DEFAULT_SPEED << 1)  // Velocidade dos tiros na tela
#define BULLET_DELAY 15 // Delay entre cada tiro do jogador

#define BULLET_H 6
#define BULLET_W 12

#define ENEMY_BULLET_H 20
#define ENEMY_BULLET_W 20

#define SHOTS_MAX 128

#define SPECIAL_DELAY 500

extern ALLEGRO_BITMAP *bullet_sprite[5];
extern Bullet shots[SHOTS_MAX];
extern unsigned int newBullet;
extern unsigned int delay;
extern Special special;

void shots_init();

bool shots_add(float x, float y, ALLEGRO_SAMPLE* sample_shot);

void enemy_shots_add(float x, float y, size_t sprite);

void update_shots(Player *player);

void draw_shots();

void destroy_shots();

void update_special(Player player);

void draw_special();

#endif // __BULLET_H__