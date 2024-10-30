#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define X_SCREEN 960 // 16 * 60
#define Y_SCREEN 540 // 9 * 60

// https://github.com/liballeg/allegro_wiki/wiki/Allegro-Vivace-%E2%80%93-Basic-game-structure
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

int main(void) {   

    init_test(al_init(), "Allegro"); // Inicializacao do allegro
    init_test(al_install_keyboard(), "teclado");
    init_test(al_init_font_addon(), "addon de font");
    init_test(al_init_ttf_addon(), "addon de ttf");
    init_test(al_init_image_addon(), "addon de imagens");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 5.0); // Tempo de atualizacao - FPS (Frames por segundo)
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); 
    ALLEGRO_FONT* font = al_load_ttf_font("assets/font/25_Sydnie.ttf", 25, ALLEGRO_ALIGN_LEFT); //NOW WE CAN CHOOSE SIZE
    ALLEGRO_DISPLAY* disp = al_create_display(X_SCREEN, Y_SCREEN); // Tamanho da janelas
    
    // Inicializar sprites principais
    ALLEGRO_BITMAP* player = init_bitmap("assets/sprite/player_idle.png");
    ALLEGRO_BITMAP* icon = init_bitmap("assets/favicon.png");

    al_set_display_icon(disp, icon);

    // Registrar fonte de eventos (teclado, tela e tempo de atualizacao)
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;
    al_start_timer(timer); // Inicio do timer do jogo

    while(true) { // Loop de jogo
        al_wait_for_event(queue, &event);

        if (event.type == 30) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            // for(int j = 1; j <= i; j++)
            al_draw_bitmap(player, 0, 0, 0);

            al_draw_text(font, al_map_rgb(255, 255, 255), (X_SCREEN >> 1), (Y_SCREEN >> 1), ALLEGRO_ALIGN_CENTRE, "Press ENTER to Continue!");
            al_flip_display(); // Flipar para nova tela
        }

        // Clicar para sair
        else if(event.type == 42) break; 
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    
    al_destroy_bitmap(player);
    al_destroy_bitmap(icon);

    return 0;
}