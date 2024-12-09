#ifndef __ENEMIE_H_
#define __ENEMIE_H_

#include "init.h"
#include "screen.h"
#include "structs.h"
#include "player.h"
#include "levels.h"
#include "env.h"

Enemy init_enemies();

bool add_enemy(Enemy *enemies, int e);

void update_enemies(Enemy *enemies, Player *player, Bullet *b, 
                    unsigned int actualScreen);

void draw_enemies(Enemy *enemies, bool debug, ALLEGRO_FONT* font);

void destroy_enemies(Enemy *e);

#endif // __ENEMIE_H_