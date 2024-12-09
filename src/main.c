#include "init.h"
#include "keyboard.h"
#include "screen.h"
#include "player.h"
#include "bullet.h"
#include "levels.h"
#include "enemy.h"
#include "boss.h"

int main(void) {

    /* Defines do tamanho da historia do jogo */
    #define TEXT_LEVEL01_SIZE 17
    #define TEXT_LEVEL02_SIZE 16
    #define TEXT_END_SIZE 14

    /* Variaveis do projeto */
    ALLEGRO_TIMER* timer;               // Timer do jogo (FRAMEREATE)
    ALLEGRO_EVENT_QUEUE* queue;         // Fila de ações do jogo
    ALLEGRO_EVENT event;                // Evento atual
    unsigned char key[ALLEGRO_KEY_MAX], // Teclado e inputs
                  choose = 0;           // Opcao de MENU INICIAL
    unsigned int actualScreen = 0;      // Tela do jogo (menu como padrao)
    bool finished = false,              // Status da execucao do jogo
         paused = false,                // Status de pause do jogo
         debug  = false;                // Status de debug do jogo
    float fade = 0.0,                   // Valor de fade do jogo
          textY = 0;                    // Posicao do texto (telas de historia)
    ALLEGRO_FONT *font;                 // Fonte do jogo
    ALLEGRO_FONT *fontAlt;              // Fonte do jogo
    Player player;                      // Jogador
    Enemy enemies;                      // Lista de inimigos do jogo
    Bullet bulletsPlayer,               // Tiros do jogador
           bulletsEnemy;                // Tiros dos inimigos
    Boss boss;                          // Chefe do jogo
    Background bg[PARALLAX_SIZE];       // Array de background parallax
    ALLEGRO_BITMAP* crtFilter;          // Filtro de CRT

    const char *text_level01[TEXT_LEVEL01_SIZE] = {
        "Level 01",
        "LOOKING FOR CRABS",
        "",
        "THE EPF (ELITE PENGUIN FORCE) WAS ATTACKED",
        "AND AMONG ALL THE AGENTS, ONLY YOU REMAINED",
        "TO GO AFTER THE GUILTY ONES",
        "",
        "WHEN YOU ENTERED THE EPF AGENCY THAT WAS ATTACKED",
        "YOU SAW A RED CRAB RUNNING AWAY",
        "AND SOON YOU REALIZED IT WAS KLUTZY",
        "",
        "YOU FOLLOWED HIM",
        "BUT HE WAS ESCAPING TOO FAST",
        "THAT'S WHY YOU TOOK YOUR OLD PARTNER",
        "THE ASTRO BARRIER SHIP",
        "",
        "MISSION: CAPTURE AND INTERROGATE KLUTZY, THE CRAB"
    };
    const char *text_level02[TEXT_LEVEL02_SIZE] = {
        "Level 02",
        "CAPTURING HERBERT",
        "",
        "INTERROGATING THE CRAB, HE TOLD YOU",
        "\"IT WASN'T ME. IT WAS HERBERT!\"",
        "\"I WAS JUST TRYING TO FIND HIM AT THE EPF\"",
        "\"BUT IT SEEMS LIKE HE HAD ALREADY ESCAPED\"",
        "\"A FEW HOURS AGO\"",
        "",
        "\"BUT I THINK I KNOW WHERE HE IS!\"",
        "\"HE SEEMS TO BE IN THE SKIES OF THE NORTH POLE\"",
        "",
        "\"I DON'T EVEN WANT TO THINK ABOUT\"",
        "\"HOW COLD IT MUST BE THERE!\"",
        "",
        "MISSION: CAPTURE AND ARREST HERBERT, THE BEAR"
    };
    const char *text_end[TEXT_END_SIZE] = {
        "CONGRATULATIONS",
        "YOU HAVE FINISHED SNOW IMPACT",
        "",
        "WITH HERBERT CAPTURED.",
        "PEACE HAS RETURNED TO PENGUIN ISLAND",
        "THE EPF HAS PUT HERBERT IN PRISON",
        "",
        "AND YOU?",
        "WELL, YOU'RE ENJOYING YOUR VACATION",
        "AFTER SAVING THE DAY, YOU DESERVE A REST",
        "",
        "THANK YOU FOR PLAYING",
        "AND KEEP PENGUINING...",
        "SEE YOU SOON, PLAYER."
    };

    /* Inicializaoes do projeto */
    init_all();
    queue           = al_create_event_queue(); 
    timer           = init_timer(FRAMERATE, queue);
    init_keyboard(key, queue);
    init_display(queue);
    player          = create_player(50, (BUFFER_H >> 1));
    font            = init_font("assets/font/average.ttf", FONT_SIZE);
    fontAlt         = init_font("assets/font/blocknon.ttf", 24); 
    crtFilter       = init_bitmap("assets/background/crtFilter.png");
    init_background(bg);

    /* Snow Impact propriamento dito */
    while(!finished) { // Loop de jogo
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER) {
            pre_draw_display();
            keyboard_options(key, &paused, &debug, actualScreen, &choose, &textY);

            switch(actualScreen) {
                // Tela de inicio
                case 0: {
                    draw_select_level(font, fontAlt, bg, choose);
                    update_select_level(key, &finished, choose, &player, bg, 
                                        &actualScreen, &boss, &bulletsPlayer, 
                                        &bulletsEnemy, &enemies);
                    break;
                }

                // Tela de historia (level 01)
                case 1: 
                    if (draw_history_level(TEXT_LEVEL01_SIZE, &textY, 
                                           text_level01, font))
                        switch_level(2, &player, bg, &actualScreen, 
                                    &boss, 
                                    &bulletsPlayer, &bulletsEnemy, 
                                    &enemies);
                    break;

                // Level 01 do jogo
                case 2:   
                    // Apenas atualiza o jogo quando nao tiver pausado
                    if(!paused) {
                        update_bullets(&bulletsPlayer, false, &player, &enemies, &boss);
                        update_bullets(&bulletsEnemy, true, &player, &enemies, &boss);
                        update_player(&player, key, &bulletsPlayer);
                        update_boss(&boss, &bulletsEnemy, &enemies, &player, 1);
                        update_background(bg);
                        update_enemies(&enemies, &player, &bulletsEnemy, actualScreen);
                        update_status();
                        update_special_bullets(player);

                        if(player.lifes == 0) finished = true;
                    }

                    draw_background(bg);
                    draw_bullets(&bulletsEnemy);
                    draw_enemies(&enemies, debug, font);
                    draw_boss(boss);
                    draw_bullets(&bulletsPlayer);
                    draw_special();
                    draw_player(player);
                    draw_status(player, font, debug, actualScreen, boss);

                    if (check_boss_death(boss, &fade, font, 
                                        "Klutzy defeated. Moving on.", 
                                        &player)) {
                        switch_level(3, &player, bg, &actualScreen, 
                                    &boss, 
                                    &bulletsPlayer, &bulletsEnemy, 
                                    &enemies);
                        fade = 0;
                    }

                    if (paused) draw_pause(font);

                    break;

                // Tela de historia (level 02)
                case 3:
                    if (draw_history_level(TEXT_LEVEL02_SIZE, &textY, 
                                           text_level02, font))
                        switch_level(4, &player, bg, &actualScreen, 
                                    &boss, 
                                    &bulletsPlayer, &bulletsEnemy, 
                                    &enemies);
                    break;

                // Level 02 do jogo
                case 4:
                    // Apenas atualiza o jogo quando nao tiver pausado
                    if(!paused) {
                        update_bullets(&bulletsPlayer, false, &player, &enemies, &boss);
                        update_bullets(&bulletsEnemy, true, &player, &enemies, &boss);
                        update_player(&player, key, &bulletsPlayer);
                        update_boss(&boss, &bulletsEnemy, &enemies, &player, 0);
                        update_background(bg);
                        update_enemies(&enemies, &player, &bulletsEnemy, actualScreen);
                        update_status();
                        update_special_bullets(player);

                        if(player.lifes == 0) finished = true;
                    }

                    draw_background(bg);
                    draw_bullets(&bulletsEnemy);
                    draw_enemies(&enemies, debug, font);
                    draw_boss(boss);
                    draw_bullets(&bulletsPlayer);
                    draw_special();
                    draw_player(player);
                    draw_status(player, font, debug, actualScreen, boss);

                    if (check_boss_death(boss, &fade, font, 
                                        "HERBERT WAS DEFEATED!!!", 
                                        &player)) {
                        switch_level(5, &player, bg, &actualScreen, 
                                    &boss, 
                                    &bulletsPlayer, &bulletsEnemy, 
                                    &enemies);
                        fade = 0;
                    }

                    if (paused) draw_pause(font);

                    break;

                // Tela de finalizacao
                case 5:
                    if (draw_history_level(TEXT_END_SIZE, &textY, 
                                           text_end, font))
                        switch_level(6, &player, bg, &actualScreen, 
                                    &boss, 
                                    &bulletsPlayer, &bulletsEnemy, 
                                    &enemies);
                    break;

                // Tela de estatisticas
                case 6:
                    draw_stats_level(font, fontAlt, bg, player);
                    break;

                default:
                    finished = true;
                    break;
            }

            al_draw_bitmap(crtFilter, 0, 0, 0); // Filtro CRT
            post_draw_display();
            keyboard_mapping(key);
        }

        update_keyboard(key, event, &finished);
    }

    /* Desalocar tudo e destruir para finalizar o jogo */
    destroy_display();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    
    al_destroy_font(font);
    al_destroy_font(fontAlt);
    al_destroy_bitmap(crtFilter);

    destroy_actual_level(actualScreen, bg, &boss, &bulletsPlayer, &bulletsEnemy, &enemies);
    destroy_player(&player);
    destroy_sprites_bullets();

    return 0;
}