#ifndef __ENEMIE_H_
#define __ENEMIE_H_

#include "utils.h"
#include "init.h"

#include "screen.h"
#include "player.h"
#include "bullet.h"
#include "levels.h"

#define MAX_ENEMIE_IN_SCREEN 20

#define ENEMIE_HP       6
#define PLAYER_DAMAGE   1

typedef struct {
    bool actived;
    float x, y, dx, dy,
          width, height;
    int hp;
    unsigned int sprite:3,  // Valor do sprite no array
                 delay,     // Valor de delay para cada tiro
                 time;      // Valor de delay para o tiro
} Enemy;

extern ALLEGRO_BITMAP *enemy_sprite[6];
extern Enemy enemies[MAX_ENEMIE_IN_SCREEN];

void init_enemies();

bool add_enemy(int e);

void enemies_update(Player *player);

void enemies_draw(bool debug, ALLEGRO_FONT* font);

void enemies_destroy();

#endif // __ENEMIE_H_