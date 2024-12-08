#include "init.h"

void init_all() {
    srand(time(NULL)); // Seed aleatoria

    initialize_or_exit(al_init(), "Allegro");
    initialize_or_exit(al_install_keyboard(), "teclado");
    initialize_or_exit(al_init_font_addon(), "addon de font");
    initialize_or_exit(al_init_ttf_addon(), "addon de ttf");
    initialize_or_exit(al_init_image_addon(), "addon de imagens");
    // initialize_or_exit(al_install_audio(), "audio");
    initialize_or_exit(al_init_acodec_addon(), "codecs de audio");
    // initialize_or_exit(al_reserve_samples(16), "reserve samples");
    initialize_or_exit(al_init_primitives_addon(), "primitives");
    // initialize_or_exit(al_reserve_samples(128), "reservas de samples");
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

ALLEGRO_SAMPLE* init_sample(const char *local) {
    ALLEGRO_SAMPLE* s = al_load_sample(local);
    if(!s) {
        printf("Não foi possível inicializar sample: (%s)\n", local);
        exit(1);
    }
    return s;
}

ALLEGRO_AUDIO_STREAM* init_music() {
    #define MUSIC_PATH "assets/sound/the-nightclub.opus"

    ALLEGRO_AUDIO_STREAM* music;
    music = al_load_audio_stream(MUSIC_PATH, 2, 2048);
    initialize_or_exit(music, "musica de fundo");
    al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_gain(music, ((float) 0.1)); // Volume da musica
    al_attach_audio_stream_to_mixer(music, al_get_default_mixer());

    return music;
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