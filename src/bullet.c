#include "bullet.h"

ALLEGRO_BITMAP *bullet_sprite;
Bullet shots[SHOTS_MAX];
unsigned int newBullet;
unsigned int delay;

void shots_init() {

    bullet_sprite = al_load_bitmap("assets/sprite/bullet/player_normal.png");
    init_test(bullet_sprite, "sprite de tiro normal");
    
    newBullet = 0;
    delay = BULLET_DELAY;

    for(size_t i = 1; i <= SHOTS_MAX; i++) {
        shots[i].used = false;
        shots[i].dx = BULLET_SPEED;
        shots[i].dy = 0;
        shots[i].x = -100;
        shots[i].y = -100;
    }
}

bool shots_add(float x, float y, ALLEGRO_SAMPLE* sample_shot) {
    al_play_sample(sample_shot, (float)0.3, 0, (float)1.5, ALLEGRO_PLAYMODE_ONCE, NULL);
    
    // Colocar o tiro na nave
    shots[newBullet].x = (x + (PLAYER_W >> 1) - BULLET_W);
    shots[newBullet].y = (y + (PLAYER_H >> 1) - (BULLET_H >> 1));

    shots[newBullet].used = true;

    newBullet++;
    if (newBullet >= 128) newBullet = 0;

    return true;
}

void shots_update() {
    for(size_t i = 1; i <= SHOTS_MAX; i++) {
        if(!shots[i].used) continue; // Se nao usado, nao renderiza
        
        // Arrumar posicao do tiro
        shots[i].x += shots[i].dx;
        shots[i].y += shots[i].dy;

        // Se chegar ao fim da tela (some)
        if(shots[i].x >= BUFFER_W) { 
            shots[i].used = false; 
            continue;
        }

        al_draw_bitmap(bullet_sprite, shots[i].x, shots[i].y, 0);
    }
}