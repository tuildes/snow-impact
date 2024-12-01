#ifndef __BULLET_H__
#define __BULLET_H__

#include "init.h"
#include "screen.h"
#include "player.h"
#include "enemie.h"
#include "boss.h"

typedef struct {
    bool used, enemy;
    size_t sprite;
    float x, y, dx, dy;
} Bullet;

typedef struct {
    bool actived, get;
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

#define SPECIAL_DELAY 500 // A cada X frames, um especial aparece na tela.

extern ALLEGRO_BITMAP *bullet_sprite[5];
extern Bullet shots[SHOTS_MAX];
extern unsigned int delay;
extern Special special;

void init_bullets();
void add_bullet(float x, float y, ALLEGRO_SAMPLE* sample_shot, 
                size_t sprite, bool enemy);
void update_bullets(Player *player, Boss *boss);
void draw_bullets();
void destroy_bullets();

void update_special_bullets(Player player);
void draw_special();

#endif // __BULLET_H__