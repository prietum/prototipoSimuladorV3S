#include <stdlib.h>
#include <box3d/box3d.h>
#include <sim.h>

Arena *sim_criaArena(Mundo *mundoPtr){
    Arena *arenaPtr = malloc(sizeof(Arena));
    Arena arena = *arenaPtr;

    //EstA struct contém as propriedades físicas das paredes.
    b3ShapeDef shapeDef_parede = b3DefaultShapeDef();

    //A seguir, as placas de madeira que formam a arena!
    b3BoxHull boxHull_paredeLateral = b3MakeBoxHull(
        COMPRIMENTO_ARENA + LARGURA_PAREDES,
        LARGURA_PAREDES,
        ALTURA_PAREDES
    );

    b3BoxHull boxHull_paredeFundo = b3MakeBoxHull(
        LARGURA_PAREDES,
        LARGURA_ARENA + LARGURA_PAREDES,
        ALTURA_PAREDES
    );

    //Aqui ficam as posições de cada placa.
    b3BodyDef bodyDef_paredeEsq = b3DefaultBodyDef();
    bodyDef_paredeEsq.position = (b3Vec3){
        
    };

    b3BodyDef bodyDef_paredeDrt = b3DefaultBodyDef();
    b3BodyDef bodyDef_paredeTop = b3DefaultBodyDef();
    b3BodyDef bodyDef_paredeBot = b3DefaultBodyDef();

    return arenaPtr;
}

Roda *sim_criaRoda(Mundo *mundoPtr){
    Roda *rodaPtr = malloc(sizeof(Roda));
    Roda roda = *rodaPtr;

    return rodaPtr;
}

Robo *sim_criaRobo(Mundo *mundoPtr){
    Robo *roboPtr = malloc(sizeof(Robo));
    Robo robo = *roboPtr;

    return roboPtr;
}

Bola *sim_criaBola(Mundo *mundoPtr){
    Bola *bolaPtr = malloc(sizeof(Bola));
    Bola bola = *bolaPtr;

    return bolaPtr;
}

Mundo *sim_criaMundo(int qntd_robos_esq, int qntd_robos_drt, int qntd_bolas){
    Mundo *mundoPtr = malloc(sizeof(Mundo));
    Mundo mundo = *mundoPtr;

    int qntd_robos_total = qntd_robos_esq+qntd_robos_drt;
    mundo.qntd_robos_esq=qntd_robos_esq;
    mundo.qntd_robos_drt=qntd_robos_drt;
    mundo.qntd_robos_total=qntd_robos_total;

    //Fazer arena
    Arena *arenaPtr = sim_criaArena(mundoPtr);
    mundo.arena = arenaPtr;

    //Fazer robôs
    for(int i=0;i<qntd_robos_total;i++){
        Robo *roboPtr = sim_criaRobo(mundoPtr);
        Robo robo = *roboPtr;
        robo.time = i>=qntd_robos_esq;
        robo.tag = i;
        mundo.robos[i]=robo;

        //Fazer rodas
    }

    //Fazer bolas
    for(int i=0;i<qntd_bolas;i++){
        Bola *bolaPtr = sim_criaBola(mundoPtr);
        Bola bola = *bolaPtr;
        mundo.bolas[i] = bola;
    }

    return mundoPtr;
}

Mundo *mundoPtr; //Mundo vazio
void sim_criaSimulacao(){
    //Mundo cheio!
    mundoPtr = sim_criaMundo(QNTD_ROBOS_ESQ,QNTD_ROBOS_DRT,QNTD_BOLAS);
}

void sim_destroiSimulacao(){
    free(mundoPtr);
}