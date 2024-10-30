#include "auxiliar.h"

void init_test(bool b, const char *n) {
    if(b) return;

    printf("Não foi possivel inicializar %s.\n", n);
    exit(1);
}

ALLEGRO_BITMAP* init_bitmap(const char *local) {

    ALLEGRO_BITMAP* bm = al_load_bitmap(local);

    if (!bm) {
        printf("Não foi possível inicializar imagem: (%s)\n", local);
        exit(1);
    }

    return bm;
}