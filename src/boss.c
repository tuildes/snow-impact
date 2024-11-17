#include "boss.h"
#include "enemie.h"

Boss init_boss(unsigned int type) {
    Boss b;

    // Paths
    const char *paths[] = {
        // Herbert
        "assets/sprite/boss/boss_02_default.png",
        "assets/sprite/boss/boss_02_bullet.png",
        "assets/sprite/boss/boss_02_damaged.png",
    };

    // Herbert
    if(!type) {
        b.active = false;
        b.hp = (20 * ENEMIE_HP);
        b.actualHp = b.hp;
        b.delay = 100;
        for(size_t i = 0; i < 3; i++)
            b.sprite[i] = init_bitmap(paths[i]);
        b.width = 220;
        b.height = 282;
        b.dy = 1;
        b.x = BUFFER_W;
        b.y = ((BUFFER_H - b.height) / 2);
    }

    return b;
}

void update_boss(Boss *boss) {
    if((mult >= 2.0) && (!boss->active)) boss->active = true; 
    if(!boss->active) return;
    if(boss->actualHp <= 0) return;  // Chefe morto

    // Se ele nao estiver na tela, o coloque
    if(boss->x >= (BUFFER_W - boss->width - 10)) (boss->x) -= 20;

    // Ataques
    const int withoutBullet = (rand() % 6);
    if((frames % boss->delay) == 0) {
        for(float y = 0; y < 6; y ++) {
            if (y != withoutBullet) 
                add_bullet(BUFFER_W, (10 + (ENEMY_BULLET_H * 3 * y)), NULL, 3, true);
        }
    }

}

void draw_boss(Boss boss) {
    if(!boss.active) return;        // Chefe nao ativo 
    if(boss.actualHp <= 0) return;  // Chefe morto

    size_t spriteBoss;

    // Sprite atual do chefe
    if(boss.actualHp >= (boss.hp * 0.75)) spriteBoss = 0;
    else if(boss.actualHp >= (boss.hp * 0.35)) spriteBoss = 1;
    else spriteBoss = 2;

    // Sprite pela vida
    al_draw_bitmap(boss.sprite[spriteBoss], 
                   boss.x, boss.y, 
                   ALLEGRO_FLIP_HORIZONTAL);

    // Vida do chefe
    al_draw_filled_rectangle((float)(BUFFER_W - (boss.actualHp) - 10), 
                            (BUFFER_H - 20), 
                            (BUFFER_W - 10), 
                            (BUFFER_H - 10), 
                            al_map_rgba(255, 255, 255, 0));
}

void destroy_boss(Boss *boss) {
    boss->active = false;
    for(size_t i = 0; i < 3; i++) al_destroy_bitmap(boss->sprite[i]);
}