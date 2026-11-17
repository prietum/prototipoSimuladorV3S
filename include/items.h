#include "box3d/id.h"
#include <box3d/box3d.h>

//'Tipo' é um struct header
//Ele indica o tipo de uma struct
//Obrigatoriamente é o primeiro membro da struct
//  1 == arena
//  2 == bola
//  3 == roda
//  4 == robô
typedef struct {
    int tipo;
} Tipo;

typedef struct {
    Tipo tipo;

    b3BodyId bodyId_paredeCima; // parede de linha lateral norte
    b3BodyId bodyId_paredeBaixo; // parede de linha lateral sul
    b3BodyId bodyId_paredeEsquerda; // parede de linha de fundo do lado esquerdo
    b3BodyId bodyId_paredeDireita; // parede de linha de fundo do lado direito
    b3BodyId bodyId_chao;
} Arena;

typedef struct {
    Tipo tipo;

    float raio;
    int bolaId;
    b3BodyId bodyId;
} Bola;

typedef struct {
    Tipo tipo;

    int comando; //[-255,255]
    int esq;
    float raio;
    float largura;

    b3JointId jointId;
    b3BodyId bodyId;
} Roda;

typedef struct {
    Tipo tipo;

    int tag;
    int time; //[0,1] == [esquerda,direita]
    int roboId;
    float dmns;

    b3BodyId bodyId;
    Roda *roda_esq;
    Roda *roda_drt;
} Robo;

typedef struct {
    Robo **robos;
    int qntd_robos_total;
    int qntd_robos_esq;
    int qntd_robos_drt;

    Bola **bolas;
    int qntd_bolas;

    Arena *arena;

    b3WorldId worldId;
} Mundo;

b3BodyId criaParede(Mundo *mundoPtr, Arena *arenaPtr, b3Pos pos, b3Vec3 size);
Arena *criaArena(Mundo *mundoPtr);
Roda *criaRoda(Mundo *mundoPtr, Robo *roboPtr, int esq);
Robo *criaRobo(Mundo *mundoPtr);
Bola *criaBola(Mundo *mundoPtr);
Mundo *criaMundo(
    void *(*criaDebugShape)(const b3DebugShape *debugShape, void *context),
     void (*destroiDebugShape)(void *userShape, void *context)
    );