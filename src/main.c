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
    #define TEXT_LEVEL02_SIZE 14
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
        "PROCURANDO CARANGUEIJOS",
        "",
        "A EPF (ELITE PENGUIM FORCE) FOI ATACADA",
        "E DENTRE TODOS OS AGENTES SOBROU APENAS VOCE",
        "PARA IR ATRAS DOS CULPADOS",
        "",
        "AO ENTRAR NA AGENCIA DA EPF QUE FOI ATACADA",
        "VOCE VIU UM CARANGUEIJO VERMELHO FUGINDO",
        "E LOGO VOCE PERCEBEU QUE ERA KLUTZY",
        "",
        "VOCE SEGUIU ELE",
        "MAS ELE ESTAVA MUITO RAPIDO NA SUA FUGA",
        "POR ISSO VOCE TEVE QUE PEGAR A SUA ANTIGA COMPANHEIRA",
        "A NAVE DO ASTRO BARRIER",
        "",
        "MISSAO: CAPTURE E INTERROGUE KLUTZY, O CARANGUEIJO"
    };
    const char *text_level02[TEXT_LEVEL02_SIZE] = {
        "Level 02",
        "CAPTURANDO HERBERT",
        "",
        "INTERROGANDO O CARANGUEIJO, ELE FALOU PARA VOCE",
        "\"NAO FUI EU. FOI O HERBERT!\"",
        "\"EU ESTAVA APENAS TENTANDO ENCONTRAR ELE NA EPF\"",
        "\"MAS PARECE QUE ELE JA TINHA FUGIDO A HORAS\"",
        "",
        "\"MAS EU ACHO QUE SEI ONDE ELE ESTA!\"",
        "\"ELE PARECE ESTAR NOS CEUS DO POLO NORTE\""
        "",
        "\"NEM QUERO PENSAR O FRIO QUE DEVE ESTAR FAZENDO LA!\"",
        "",
        "MISSAO: CAPTURE E PRENDA HERBERT, O URSO"
    };
    const char *text_end[TEXT_END_SIZE] = {
        "PARABENS",
        "VOCE FINALIZOU SNOW IMPACT",
        "",
        "COM HERBERT CAPTURADO.",
        "A PAZ VOLTOU PARA A ILHA PENGUIM",
        "A EPF COLOCOU HERBERT NA PRISAO",
        "",
        "E VOCE?",
        "BOM, VOCE ESTA APROVEITANDO SUAS FERIAS",
        "DEPOIS DE SALVAR O DIA, VOCE MERECE UM DESCANSO",
        "",
        "OBRIGADO VOCE POR JOGAR",
        "E SIGA PINGUINANDO...",
        "ATE BREVE, JOGADOR."
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
                    if(!paused) {
                        update_status();
                    }

                    check_boss_death(boss, &fade, font, 
                                    "Klutzy derrotado. Prosseguindo.", 
                                    &player);

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
                        update_boss(&boss, &bulletsEnemy, &enemies, &player);
                        update_background(bg);
                        update_enemies(&enemies, &player, &bulletsEnemy);
                        update_status();

                        if(player.lifes == 0) finished = true;
                    }

                    draw_background(bg);
                    draw_bullets(&bulletsEnemy);
                    draw_enemies(&enemies, debug, font);
                    draw_boss(boss);
                    draw_bullets(&bulletsPlayer);
                    draw_player(player);
                    draw_status(player, font, debug, actualScreen, boss);

                    if (check_boss_death(boss, &fade, font, 
                                        "HERBERT FOI DERROTADO!!!", 
                                        &player))
                        switch_level(5, &player, bg, &actualScreen, 
                                    &boss, 
                                    &bulletsPlayer, &bulletsEnemy, 
                                    &enemies);

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