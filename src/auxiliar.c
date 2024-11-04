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

bool collide(float ax1, float ay1, float ax2, float ay2,
             float bx1, float by1, float bx2, float by2) {

    if(ax1 > bx2) return false;
    if(ax2 < bx1) return false;
    if(ay1 > by2) return false;
    if(ay2 < by1) return false;

    return true;

}