#ifndef __BOSS_H__
#define __BOSS_H__

#include "init.h"
#include "screen.h"
#include "player.h"

typedef struct {
    bool active;
    unsigned int hp, actualHp, delay;
    ALLEGRO_BITMAP *sprite[3];
    float x, y, dy, 
          width, height;
} Boss;

Boss init_boss(unsigned int type);

void update_boss(Boss *boss);

void draw_boss(Boss boss);

void destroy_boss(Boss *boss);

#endif // __BOSS_H__