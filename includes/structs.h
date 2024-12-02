#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <allegro5/allegro_image.h>

typedef struct {
    float x, y;
    unsigned int lifes:2,
                 delay;
    long invincibility;
    double time;
    unsigned int kills;
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

#endif // __PLAYER_STRUCT_H__