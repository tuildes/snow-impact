#ifndef __BOSS_H__
#define __BOSS_H__

#include "init.h"
#include "screen.h"
#include "structs.h"
#include "enemy.h"

Boss init_boss(unsigned int type);

void update_boss(Boss *boss, Bullet *b, Enemy *enemies, Player *player, 
                 bool level);

void draw_boss(Boss boss);

void destroy_boss(Boss *boss);

int check_boss_death(Boss boss, float *fade, ALLEGRO_FONT* font, 
                      const char *victoryText, Player *p);

#endif // __BOSS_H__