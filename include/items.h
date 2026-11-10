#include "box3d/id.h"
#include <box3d/box3d.h>

typedef struct {
    b3BodyId bodyId_parede1; // parede de linha lateral norte
    b3BodyId bodyId_parede2; // parede de linha lateral sul
    b3BodyId bodyId_parede3; // parede de linha de fundo do lado esquerdo
    b3BodyId bodyId_parede4; // parede de linha de fundo do lado direito
    b3BodyId bodyId_chao;
} Arena;

typedef struct {
    float raio;
    int bolaId;
    b3BodyId bodyId;
} Bola;

typedef struct {
    int comando; //[-255,255]
    int esq;
    float raio;
    float largura;

    b3JointId jointId;
    b3BodyId bodyId;
} Roda;

typedef struct {
    int tag;
    int time; //[0,1] == [esquerda,direita]
    int roboId;
    float dmns;

    b3BodyId bodyId;
    Roda *roda_esq;
    Roda *roda_drt;
} Robo;

typedef struct {
    Robo *robos;
    int qntd_robos_total;
    int qntd_robos_esq;
    int qntd_robos_drt;

    Bola *bolas;
    int qntd_bolas;

    Arena *arena;

    b3WorldId worldId;
} Mundo;

Arena *criaArena(Mundo *mundoPtr);
Roda *criaRoda(Mundo *mundoPtr, Robo *roboPtr, int esq);
Robo *criaRobo(Mundo *mundoPtr);
Bola *criaBola(Mundo *mundoPtr);
Mundo *criaMundo(
    void *(*criaDebugShape)(const b3DebugShape *debugShape, void *context),
     void (*destroiDebugShape)(void *userShape, void *context)
    );