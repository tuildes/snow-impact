#ifndef __BULLET_H__
#define __BULLET_H__

#include "init.h"
// #include "enemie.h"
// #include "boss.h"

typedef struct Bullet {
    size_t sprite;
    float x, y, dx, dy;
    struct Bullet *next;
} Bullet;

typedef struct {
    bool actived, get;
    float time;
    float x, y, dx, width, height;
    unsigned int sprite:1;
} Special;

#define BULLET_SPEED (PLAYER_DEFAULT_SPEED << 1)  // Velocidade dos tiros na tela
#define BULLET_DELAY 25 // Delay entre cada tiro do jogador

#define BULLET_H 4
#define BULLET_W 12

#define ENEMY_BULLET_H 6
#define ENEMY_BULLET_W 6

#define SPECIAL_DELAY 500 // A cada X frames, um especial aparece na tela.

extern ALLEGRO_BITMAP *bullet_sprite[5];
extern Special special;

Bullet init_bullets();

void add_bullet(float x, float y, Bullet *bullets, size_t sprite);
void update_bullets(Bullet *bplayer);

void draw_bullets(Bullet *bplayer);
void destroy_bullets(Bullet *bplayer);

// void update_special_bullets(Player player);
// void draw_special();

#endif // __BULLET_H__