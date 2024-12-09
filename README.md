<!-- HEADER -->
<p align="center">
  <img alt="Image in picture" src="https://github.com/user-attachments/assets/5449d970-b87b-467a-94ed-c4761ff358d4" height="120">
  <h3 align="center">Snow Impact</h3>
  <p align="center">Jogo de navinha inspirado em Space Impact e Club Penguin</p>
</p>
<!-- HEADER -->

## Sobre

O projeto "Snow Impact" consiste em uma reimaginação do clássico jogo Space Impact, mas feito totalemente em C e Allegro5, agora com temática de Club Penguin.

O Jogo conta com:
* Tela de início
* 2 fases com bosses icônicos do universo do Club Penguin
* Uma história cativante
* 9 diferentes inimigos
* Uma tela de estatísticas
* E mais...

## Screenshots do projeto

* Tela de inicio:
![Tela de inicio](.github/screenshots/start.png)

* História:
![História do jogo](.github/screenshots/history.png)

* Gameplay:
![Gameplay mostrando nave e inimigos](.github/screenshots/level2.png)

* Boss:
![Chefão herbert](.github/screenshots/herbert.png)

* Tela de fim de jogo:
![Tela de fim de jogo](.github/screenshots/end.png)

## Como jogar

* **[Setas do teclado]** para movimentação do jogo
* **[Espaço]** para atirar e interagir
* **[ESC]** ou **[P]** para pausar o jogo
* **[D]** para habilitar informações de depuração

* **Botão de sair da tela** para sair

## Como mudar a dificuldade e outros parâmetros

Basta ir no arquivo `includes/env.h` e editar suas informações e defines para adequar o jogo para sua dificuldade e necessidade.
Por exemplo, para trocar o tamanho da tela do jogo:
```c
#define DISP_SCALE  4 // Troque para o valor que preferir (inteiro como 1, 2, ...)
```

<br />

<p align="center">Criado com 💙 por <a href="https://github.com/tuildes">tuildes</a></p>
