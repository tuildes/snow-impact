# Projeto [trabalho #2 PROG2]

O projeto, que será realizado totalmente em linguagem C e suas bibliotecas, é uma replicação do clássico jogo **"Space Impact"**. Que consiste em um jogo de nave shooter dividido em fases, nas fases há obstáculos, cenários, inimigos e um chefe para a progressão.

Este projeto se chamará "Snow Impact" e terá uma forte inspiração e assets pegos do jogo "Club Penguin", um jogo da RocketSnail e Disney.

# Ideias e progressão do jogo

## Player (jogador controlável)

-   O player será uma nave que anda para frente e para trás sem alternar ou espelhar a nave na movimentação
-   Pequenas animações de movimentação
-   **Sprite normal**
    -   ![Nave do Astro Barrier](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_ec42fc47e10deb5476aab04aab578cd2.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294415&Signature=ihvgaCyNX7MtelXWEwfbbjfIxXs%3D)
-   **Sprite de dano (perda de vida)**
    -   ![Nave do Astro Barrier destruida](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_11328f29c8f0974279971657b0db81d5.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294344&Signature=SbjAImfdWdpN%2FT%2B42ieVKn543NU%3D)

### Tiros

-   O jogo conterá 4 tipos principais de tiros:
    -   **Tiro normal** (X de dano)
        -   Tiro default que é infinito!
        -   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_c17d0be0eea50287d93f5dbf6c16844e.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294455&Signature=d48W2hGL7EZSgQQ1GosDdDqfF7A%3D)
    -   **Tiro explosivo** (2X de dano)
        -   Tiro que quando pego dura 3 segundos
        -   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_1ae2128580aeba34636094f5e4c15d5c.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294464&Signature=u8Oql5p8Sm2ZzIlDzFa8%2Bn%2FGTQU%3D)
    -   **Tiro congelante** (X de dano e causa lentidão no inimigo)
        -   _Se possível trocará a cor do sprite do inimigo (incerto)_
        -   Tiro que quando pego dura 4 segundos
        -   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_731d14512ed29ff8f19118d2fd252a0f.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294472&Signature=otwI3F9avZw0TH4MjktI555lwZU%3D)
    -   **Tiro perfurante** (X de dano e atravessa os inimigos)
        -   Tiro que quando pego dura 5 segundos
        -   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_a697ad5aee90db0a12c745e3e853657f.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294480&Signature=5pVN2pjW%2B7XtyCCRNOFZZ65JJL8%3D)

## História e cenários

![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_4e6509c47d9f2f28b32d6cc3f003f3c1.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294497&Signature=1t03ofhQyQw1Hz6gi%2FSlmy7OtGg%3D)

### Tela de início (extra)

-   Tela de seleção para COMEÇAR ou SAIR
-   Como jogar
-   Versão do projeto
-   Algumas informações gerais

### Tela de introdução (extra)

-   Tela estilo STAR WARS
-   Conta o enredo do jogo (introdução)

### Fase 01

-   Cenário de fábrica
-   Inimigos são descritos na seção abaixo
-   Nome: "Fase 01 - resolvendo problemas de carangueijo"
-   Inimigos: robôs
-   Chefe: Klutzy, o carangueijo

### Fase 02

-   Cenário de campo nevado
-   Inimigos são descritos na seção abaixo
-   Nome: "Fase 02 - capturando Herbert"
-   Inimigos: capangas de neve
-   Chefe: Herbert, o urso

### Tela de finalização (extra)

-   Tela estilo STAR WARS
-   Conta a finalização do enredo do jogo

### Tela de estatísticas (extra)

-   Tela de estatísticas que mostra um resumo ao jogador
    -   Tempo de jogo
    -   Quantidade de mortes
    -   Inimigos derrotados
    -   PowerUps (tiros especiais) coletados
    -   _Uma frase especiais dando parabéns ao jogador e agradecendo por jogar_

## Inimigos

### Fase 01

-   Inimigo 01 (whell bot)
    -   Inimigo imóvel
    -   Não arremesa nada
    -   Vida comum (X)
    -   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_c1e77a2cce1f90250f18fce71e521214.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294514&Signature=EyNIJVBJz9fs4wR9HRqpIdBVIIw%3D)
-   Inimigo 02 (snow bot)
    -   Arremesso de bola de neve
    -   Vida comum (X)
    -   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_833c3f023d02d410d54a0df5fc9056b9.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294526&Signature=s5C2gSnOquc9i8DJ8MaN4AZI0rM%3D)
-   Inimigo 03 (ultimate proto-bot 1000)
    -   Vida dobrada (2X)
    -   Movimentação lenta
    -   Arremesso de controles
    -   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_f84d1fa9c8733b16ee1af94bdeac9d93.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294533&Signature=mB%2Fa6%2BBME8Dmq3ijvWPp5y1t95M%3D)

### Fase 02

-   Inimigo 01 (Sly)
    -   Inimigo com quantidade de vida média (x)
    -   Arremessa bolas de neve
    -   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_bc31e5de13906b4445c81f78dbe908b0.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294540&Signature=07gna183HlN5lDeOVZBl2aQi4q8%3D)
-   Inimigo 02 (Scrap)
    -   Inimigo com menos vida que os inimigos (x/2)
    -   Arremessa bolas de neve derretidas
    -   Movimentação rápida
    -   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_d1a81abd5d1468d610011d08a340ca87.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294550&Signature=aGccv5q29zwYgW%2F%2FA7Je19qeqzg%3D)
-   Inimigo 03 (Tank)
    -   Inimigo básico que só irá em direção do jogador
    -   Movimentação lenta
    -   Não arremessa nada
    -   Possívelmente mais vida que os inimigos comuns (2x)
    -   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_9a6f75040e136f0ca570cd661d818783.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294561&Signature=tKJBnvdZRLMW5r4nMU0U0qDOIJM%3D)

## Chefes

### Fase 01

-   Chefe: Klutzy, o carangueijo
-   Vida: 30x
-   Ataques: indefinidos
    -   Arremesso
    -   Investida
-   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_84ca661819b5a7338b751b20ae7bbace.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294592&Signature=PGafH0luTh%2FDDUR02nQPjZ3Z438%3D)

### Fase 02

-   Chefe: Herbert, o urso
-   Vida: 50x
-   Ataques: indefinidos
    -   Arremesso
    -   Criar uma onda de inimigos
    -   "ataque": sorteia um número 1 a 6
        -   1: dá uma vida a mais ao jogador (max: 3)
        -   2-3: cria um power up aleatório
        -   4: faz um arremesso
        -   5: cria o máximo de inimigos na tela
        -   6: cura o chefe (pouco, mas o suficiente para incomodar)
-   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_6685881611fbbbbbe1255454a291c3ee.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294599&Signature=o2Wr%2BwyfFpd4SavMSZD%2BGg3%2BH04%3D)

## Layout básico

-   Vai ser completo para o futuro...
-   Contando com parallax e cenários de fundo
-   ![image](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_d683f78f825b6c9db7d61325bbb12640.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1730294606&Signature=o%2FtE592vMJv9zoLG8VHJuzdt4oo%3D)

## Músicas e sons

-   Todas as músicas serão do jogo "Astro Barrier (2006)", também original do Club penguin.
-   Música de fundo
-   Sons de tiro, fase completa, game over, inimigo destruído ...

---

# Segmentação do trabalho

-   Pasta de ASSETS
    -   Imagens e sprites
    -   Audios
-   Pasta de SRC
    -   Main.c
    -   Bullets.c
    -   Player.c
    -   Joystick.c
-   Makefile
-   README.md

## Relações

# Cronograma

-   A ideia é a cada final de semana ter um projeto ALPHA entregável
    -   Ou seja, uma parte entregável e funcional do projeto, sem problemas ou funcionamentos inacabados.

| Semana          | Desenvolvimento                                  |
| :-------------- | :----------------------------------------------- |
| 28/10 - 03/11   | Projeto, código base e player                    |
| 04/10 - 10/11   | Tiros, Inimigos e danos, Sistema de vida         |
| 11/10 - 17/11   | Fase 01 e fase 02, transição de fases e cenários |
| 18/10 - 24/11   | Chefes e audios, tela de start, animações        |
| 25/10 - 01/12   | Telas extras, power ups e primeira finalização   |
| 02/10 - 08/12   | Pequenos ajustes e entregas                      |
| _09/10 - 11/12_ | _Defesa do trabalho_                             |

---

Todos os alunos devem entregar um documento em PDF, organizado por seções,
descrevendo o projeto inicial de implementação.
Esse documento deve conter as seguintes informações: segmentação do trabalho (quais
arquivos e módulos você pretende criar e por quê), dependências entre os módulos a
serem desenvolvidos, a ordem de desenvolvimento desses módulos e, por fim, um
cronograma estimado para o desenvolvimento do programa. O PDF do projeto deverá ser
entregue até o dia 05/11, no Moodle
