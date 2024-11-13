#include "levels.h"

void init_background(Background *b) {

    b[0].image = init_bitmap("assets/background/level1-1.png");
    b[0].velX = 0.5;

    b[1].image = init_bitmap("assets/background/level1-2.png");
    b[1].velX = 2;

    b[2].image = init_bitmap("assets/background/level1-3.png");
    b[2].velX = 3;

    for(size_t i = 0; i < PARALLAX_SIZE; i++) {
        b[i].height = BUFFER_H;
        b[i].width = BUFFER_W;
        b[i].x = BUFFER_W;
        b[i].y = 0;
        b[i].velY = 0;
    }
}

void update_background(Background *b) {
    for(size_t i = 0; i < PARALLAX_SIZE; i++) {
        b[i].x -= b[i].velX;
        if((b[i].x + (float)b[i].width) <= 0) b[i].x = BUFFER_W;
    }
}

void draw_background(Background *b) {
    for(size_t i = 0; i < PARALLAX_SIZE; i++) {
        al_draw_bitmap(b[i].image, b[i].x, b[i].y, 0);
        al_draw_bitmap(b[i].image, (b[i].x + (float)b[i].width), b[i].y, 0);
        al_draw_bitmap(b[i].image, (b[i].x - (float)b[i].width), b[i].y, 0);
    }
}

void destroy_backround(Background *b) {
    for(size_t i = 0; i < PARALLAX_SIZE; i++)
        al_destroy_bitmap(b[i].image);
}