#ifndef SIMULACAO
#define SIMULACAO

#include <box3d/box3d.h>
#include <medidas.h>
#include <partida.h>

typedef struct Arena {
    b3BodyId bodyId_parede1; // parede de linha lateral norte
    b3BodyId bodyId_parede2; // parede de linha lateral sul
    b3BodyId bodyId_parede3; // parede de linha de fundo do lado esquerdo
    b3BodyId bodyId_parede4; // parede de linha de fundo do lado direito
    b3BodyId bodyId_chao;
} Arena;

typedef struct Bola {
    b3BodyId bodyId;
} Bola;

typedef struct Roda {
    int comando; //[-255,255]

    b3BodyId bodyId;
} Roda;

typedef struct Robo {
    int tag;
    int time; //[0,1] == [esquerda,direita]

    b3BodyId bodyId;
    Roda *roda_esq;
    Roda *roda_drt;
} Robo;

typedef struct Mundo {
    Robo *robos;
    int qntd_robos_total;
    int qntd_robos_esq;
    int qntd_robos_drt;

    Bola *bolas;
    int qntd_bolas;

    Arena *arena;

    b3WorldId worldId;
} Mundo;

void   sim_criaSimulacao();
void   sim_destroiSimulacao();
void   sim_passo(float dt);
Mundo *sim_criaMundo(int qntd_robos_esq, int qntd_robos_drt, int qntd_bolas); //Cria o mundo, que contém tudo o que simulamos
Arena *sim_criaArena(Mundo *mundoPtr); //Cria a arena, que é onde os robôs jazem
Roda  *sim_criaRoda(Mundo *mundoPtr); //Cria rodas presas aos robôs por juntas de motor
Robo  *sim_criaRobo(Mundo *mundoPtr);
Bola  *sim_criaBola(Mundo *mundoPtr);

#endif