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
    
    //                             norte                             
    //                                                               
    //            . - - .------------1-------------. - - .       
    //                  |                          |            
    //            |     3                          5     |      
    //                  |                          |            
    //            .--7--'                          '--9--.      
    //            |                                      |      
    //esquerda  11|                  0                   |12  direita  
    //            |                                      |      
    //            '--8--.                          .--10-'      
    //                  |                          |            
    //            |     4                          6     |      
    //                  |                          |            
    //            ' - - '------------2-------------' - - '      
    //                                                               
    //                              sul                              

    //Ṕlacas de madeira que formam o campo
    b3BodyId bodyId_chao;             //  0 Chão da arena
    b3BodyId bodyId_parede_lateralN;  //  1 Parede de linha lateral norte
    b3BodyId bodyId_parede_lateralS;  //  2 Parede de linha lateral sul
    b3BodyId bodyId_parede_fundoEsqN; //  3 Parede de linha de fundo do lado esquerdo norte
    b3BodyId bodyId_parede_fundoEsqS; //  4 Parede de linha de fundo do lado esquerdo sul
    b3BodyId bodyId_parede_fundoDrtN; //  5 Parede de linha de fundo do lado direito norte
    b3BodyId bodyId_parede_fundoDrtS; //  6 Parede de linha de fundo do lado direito sul
    b3BodyId bodyId_parede_traveEsqN; //  7 Parede de trave do lado esquerdo norte
    b3BodyId bodyId_parede_traveEsqS; //  8 Parede de trave do lado esquerdo sul
    b3BodyId bodyId_parede_traveDrtN; //  9 Parede de trave do lado direito norte
    b3BodyId bodyId_parede_traveDrtS; // 10 Parede de trave do lado direito sul
    b3BodyId bodyId_parede_golEsq;    // 11 Parede de gol lado esquerdo
    b3BodyId bodyId_parede_golDrt;    // 12 Parede de gol lado direito
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