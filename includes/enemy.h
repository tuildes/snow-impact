#ifndef __ENEMIE_H_
#define __ENEMIE_H_

#include "init.h"
#include "screen.h"
#include "structs.h"
#include "player.h"
#include "levels.h"

#define MAX_ENEMIE_IN_SCREEN 20

#define ENEMY_HP       3
#define ENEMY_DELAY    50
#define ENEMY_SPAWN    120

#define PLAYER_DAMAGE  10

Enemy init_enemies();

bool add_enemy(Enemy *enemies, int e);

void update_enemies(Enemy *enemies, Player *player, Bullet *b);

void draw_enemies(Enemy *enemies, bool debug, ALLEGRO_FONT* font);

void destroy_enemies(Enemy *e);

#endif // __ENEMIE_H_