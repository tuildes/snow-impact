#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <allegro5/allegro_image.h>

typedef struct {
    float x, y;
    unsigned int lifes:2,
                 delay;
    long invincibility;
    double time;
    unsigned int kills, bullets;
    ALLEGRO_BITMAP *sprite;
} Player;

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

typedef struct {
    bool active;
    unsigned int hp, delay;
    int actualHp;
    ALLEGRO_BITMAP *sprite[3];
    float x, y, dy, 
          width, height;
} Boss;

typedef struct Enemy {
      bool actived;
      float x, y, dx, dy,
            width, height;
      int hp;
      bool iced;
      unsigned int sprite:4,  // Valor do sprite no array
                   delay,     // Valor de delay para cada tiro
                   time;      // Valor de delay para o tiro
      struct Enemy *next;
} Enemy;

#endif // __PLAYER_STRUCT_H__