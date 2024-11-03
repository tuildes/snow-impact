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

void init_all() {
    init_test(al_init(), "Allegro");
    init_test(al_install_keyboard(), "teclado");
    init_test(al_init_font_addon(), "addon de font");
    init_test(al_init_ttf_addon(), "addon de ttf");
    init_test(al_init_image_addon(), "addon de imagens");
    init_test(al_install_audio(), "audio");
    init_test(al_init_acodec_addon(), "codecs de audio");
    init_test(al_reserve_samples(16), "reserve samples");
    init_test(al_init_primitives_addon(), "primitives");
}