#include "init.h"

void init_all() {
    srand(time(NULL)); // Seed aleatoria

    initialize_or_exit(al_init(), "Allegro");
    initialize_or_exit(al_install_keyboard(), "teclado");
    initialize_or_exit(al_init_font_addon(), "addon de font");
    initialize_or_exit(al_init_ttf_addon(), "addon de ttf");
    initialize_or_exit(al_init_image_addon(), "addon de imagens");
    initialize_or_exit(al_init_acodec_addon(), "codecs de audio");
    initialize_or_exit(al_init_primitives_addon(), "primitives");
}

void initialize_or_exit(bool fc, const char *n) {
    if(fc) return;

    printf("Não foi possivel inicializar %s.\n", n);
    exit(1);
}

ALLEGRO_BITMAP* init_bitmap(const char *local) {
    ALLEGRO_BITMAP* bm = al_load_bitmap(local);
    if(!bm) {
        printf("Não foi possível inicializar imagem: (%s)\n", local);
        exit(1);
    }
    return bm;
}

ALLEGRO_FONT* init_font(const char *local, int fontSize) {
    ALLEGRO_FONT* f = al_load_ttf_font(local, fontSize, 0);
    if(!f) {
        printf("Não foi possível inicializar fonte: (%s)\n", local);
        exit(1);
    }
    return f;
}

ALLEGRO_TIMER* init_timer(float framerate, ALLEGRO_EVENT_QUEUE* queue) {
    ALLEGRO_TIMER* t = al_create_timer(1.0 / framerate);
    if(!t) {
        printf("Não foi possível inicializar o timer\n");
        exit(1);
    }

    al_register_event_source(queue, al_get_timer_event_source(t));
    al_start_timer(t); // Inicio do timer do jogo
    return t;
}