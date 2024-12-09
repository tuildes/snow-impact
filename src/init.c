#include "init.h"

void init_all() {
    srand(time(NULL)); // Seed aleatoria

    initialize_or_exit(al_init(), "Allegro");
    initialize_or_exit(al_install_keyboard(), "keyboard");
    initialize_or_exit(al_init_font_addon(), "font addon");
    initialize_or_exit(al_init_ttf_addon(), "ttf addon");
    initialize_or_exit(al_init_image_addon(), "image addon");
    initialize_or_exit(al_init_primitives_addon(), "primitives");
}

void initialize_or_exit(bool fc, const char *n) {
    if(fc) return;

    printf("[ERROR] Unable to initialize %s.\n", n);
    exit(1);
}

ALLEGRO_BITMAP* init_bitmap(const char *local) {
    ALLEGRO_BITMAP* bm = al_load_bitmap(local);
    if(!bm) {
        printf("[ERROR] Unable to initialize image: (%s)\n", local);
        exit(1);
    }
    return bm;
}

ALLEGRO_FONT* init_font(const char *local, int fontSize) {
    ALLEGRO_FONT* f = al_load_ttf_font(local, fontSize, 0);
    if(!f) {
        printf("[ERROR] Unable to initialize font: (%s)\n", local);
        exit(1);
    }
    return f;
}

ALLEGRO_TIMER* init_timer(float framerate, ALLEGRO_EVENT_QUEUE* queue) {
    ALLEGRO_TIMER* t = al_create_timer(1.0 / framerate);
    if(!t) {
        printf("[ERROR] Unable to initialize timer\n");
        exit(1);
    }

    al_register_event_source(queue, al_get_timer_event_source(t));
    al_start_timer(t); // Inicio do timer do jogo
    return t;
}