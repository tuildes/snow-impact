#ifndef __ENEMIE_H_
#define __ENEMIE_H_

#include "init.h"
#include "screen.h"
#include "player.h"
#include "bullet.h"
#include "levels.h"

#define MAX_ENEMIE_IN_SCREEN 20

#define ENEMIE_HP       6
#define PLAYER_DAMAGE   1

typedef struct Enemy {
      bool actived;
      float x, y, dx, dy,
            width, height;
      int hp;
      bool iced;
      unsigned int sprite:3,  // Valor do sprite no array
                  delay,     // Valor de delay para cada tiro
                  time;      // Valor de delay para o tiro
      struct Enemy *next;
} Enemy;

extern ALLEGRO_BITMAP *enemy_sprite[7];

Enemy init_enemies();

bool add_enemy(Enemy *enemies, int e);

void update_enemies(Enemy *enemies, Player *player, Bullet *b);

void draw_enemies(Enemy *enemies, bool debug, ALLEGRO_FONT* font);

void destroy_enemies(Enemy *e);

#endif // __ENEMIE_H_