#include "box3d/collision.h"
#include "box3d/id.h"
#include "box3d/math_functions.h"
#include "box3d/types.h"
#include "raymath.h"
#include <config.h>

#include <stdio.h>
#include <stdlib.h>

#include <box3d/box3d.h>
#include <items.h>

b3BodyId criaParede(Mundo *mundoPtr, Arena *arenaPtr, b3Pos pos, b3Vec3 size){
    printf("criaParede\n");

    //printf("criaParede bodyDef\n");
    //printf("criaParede mundo.worldId: %d\n", mundoPtr->worldId.index1);
    b3BodyDef bodyDef = b3DefaultBodyDef();
    bodyDef.position = pos;
    bodyDef.type = b3_staticBody;
    b3BodyId bodyId = b3CreateBody(mundoPtr->worldId, &bodyDef);

    //printf("criaParede boxHull\n");
    b3BoxHull boxHull = b3MakeBoxHull(size.x/2,size.y/2,size.z/2);
    b3ShapeDef shapeDef = b3DefaultShapeDef();
    shapeDef.userData = (void*)arenaPtr;
    b3CreateHullShape(bodyId, &shapeDef, &boxHull.base);

    return bodyId;
}

Arena *criaArena(Mundo *mundoPtr){
    printf("criaArena\n");
    
    Arena *arenaPtr = malloc(sizeof(Arena));
    Arena arena = *arenaPtr;

    b3BodyId bodyId_chao           = criaParede(mundoPtr, arenaPtr, POSICAO_CHAO,       DMNS_CHAO);
    b3BodyId bodyId_paredeCima     = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_CIMA, DMNS_PAREDE_LATERAL);
    b3BodyId bodyId_paredeBaixo    = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_BAIXO, DMNS_PAREDE_LATERAL);
    b3BodyId bodyId_paredeEsquerda = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_ESQUERDA, DMNS_PAREDE_FUNDO);
    b3BodyId bodyId_paredeDireita  = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_DIREITA, DMNS_PAREDE_FUNDO);

    arenaPtr->tipo.tipo = 1;
    arenaPtr->bodyId_chao = bodyId_chao;
    arenaPtr->bodyId_paredeCima = bodyId_paredeCima;
    arenaPtr->bodyId_paredeBaixo = bodyId_paredeBaixo;
    arenaPtr->bodyId_paredeEsquerda = bodyId_paredeEsquerda;
    arenaPtr->bodyId_paredeDireita = bodyId_paredeDireita;

    return arenaPtr;
}

Roda *criaRoda(Mundo *mundoPtr, Robo *roboPtr, int esq){
    printf("criaRoda\n");
    Roda *rodaPtr = malloc(sizeof(Roda));

    //b3Pos posRobo = b3Body_GetPosition(roboPtr->bodyId);
    esq=1-esq*2;
    b3Pos offRoda = (b3Pos){
        (DMNS_ROBO/2 + PROFUNDIDADE_RODA)*esq,
        -DMNS_ROBO/2 + RAIO_RODA - ALTURA_RODA,
        0.0f
    };
    b3Pos posRoda = b3Body_GetWorldPoint(roboPtr->bodyId,offRoda);

    b3BodyDef bodyDef = b3DefaultBodyDef();
    bodyDef.type = b3_dynamicBody;
    bodyDef.position = posRoda;
    b3BodyId bodyId = b3CreateBody(mundoPtr->worldId, &bodyDef);

    b3HullData *cylHull = b3CreateCylinder(LARGURA_RODA, RAIO_RODA, LARGURA_RODA/2, 20);
    b3ShapeDef shapeDef = b3DefaultShapeDef();
    shapeDef.userData = (void*)rodaPtr;
    b3CreateHullShape(bodyId, &shapeDef, cylHull);

    //printf("criaRoda mundoPtr->worldId: %d\n",mundoPtr->worldId.index1);
    //printf("criaRoda roboPtr->bodyId.world0: %d\n",roboPtr->bodyId.world0);
    //printf("criaRoda bodyId.world0: %d\n",bodyId.world0);
    b3WheelJointDef jointDef = b3DefaultWheelJointDef();
    jointDef.base.collideConnected = false;
    jointDef.base.bodyIdA = roboPtr->bodyId;
    jointDef.base.bodyIdB = bodyId;
    jointDef.base.localFrameA = b3Transform_identity;
    jointDef.base.localFrameB = b3Transform_identity;
    b3JointId jointId = b3CreateWheelJoint(mundoPtr->worldId, &jointDef);

    rodaPtr->tipo.tipo = 3;
    rodaPtr->bodyId = bodyId;
    rodaPtr->jointId = jointId;
    rodaPtr->comando = 0;
    rodaPtr->esq = esq;
    rodaPtr->raio = RAIO_RODA;
    rodaPtr->largura = LARGURA_RODA;

    return rodaPtr;
}

Robo *criaRobo(Mundo *mundoPtr){
    printf("criaRobo\n");
    
    Robo *roboPtr = malloc(sizeof(Robo));

    b3BodyDef bodyDef = b3DefaultBodyDef();
    bodyDef.type = b3_dynamicBody;
    bodyDef.position = ORIGEM;
    b3BodyId bodyId = b3CreateBody(mundoPtr->worldId,&bodyDef);

    b3BoxHull boxHull = b3MakeBoxHull(DMNS_ROBO/2, DMNS_ROBO/2, DMNS_ROBO/2);
    b3ShapeDef shapeDef = b3DefaultShapeDef();
    shapeDef.userData = (void*)roboPtr;
    b3CreateHullShape(bodyId, &shapeDef, &boxHull.base);

    //printf("criaRobo bodyId.world0: %d\n",bodyId.world0);
    //printf("criaRobo bodyId.index1: %d\n",bodyId.index1);
    roboPtr->tipo.tipo = 4;
    roboPtr->bodyId = bodyId;
    roboPtr->dmns = DMNS_ROBO;
    roboPtr->roda_drt = criaRoda(mundoPtr, roboPtr, 0);
    roboPtr->roda_esq = criaRoda(mundoPtr, roboPtr, 1);

    return roboPtr;
}

Bola *criaBola(Mundo *mundoPtr){
    printf("criaBola\n");
    
    Bola *bolaPtr = malloc(sizeof(Bola));

    b3BodyDef bodyDef = b3DefaultBodyDef();
    bodyDef.type = b3_dynamicBody;
    bodyDef.position = POSICAO_BOLA_INICIO;
    b3BodyId bodyId = b3CreateBody(mundoPtr->worldId, &bodyDef);

    b3Sphere sphere = {.center = 0, .radius = RAIO_BOLA};
    b3ShapeDef shapeDef = b3DefaultShapeDef();
    shapeDef.userData = (void*)bolaPtr;
    b3CreateSphereShape(bodyId, &shapeDef, &sphere);

    bolaPtr->bodyId = bodyId;
    bolaPtr->tipo.tipo = 2;
    bolaPtr->raio = RAIO_BOLA;

    return bolaPtr;
}

Mundo *criaMundo(
    void *(*criaDebugShape)(const b3DebugShape *debugShape, void *context),
    void (*destroiDebugShape)(void *userShape, void *context))
{
    printf("criaMundo\n");
    ///////////Fazer o mundo em si
    Mundo *mundoPtr = malloc(sizeof(Mundo));

    //printf("criaMundo worldDef\n");
    b3WorldDef worldDef = b3DefaultWorldDef();
    worldDef.gravity = (b3Vec3){0.0f,-9.8f,0.0f};
    worldDef.createDebugShape = criaDebugShape;
    worldDef.destroyDebugShape = destroiDebugShape;

    //printf("criaMundo worldId\n");
    b3WorldId worldId = b3CreateWorld(&worldDef);
    mundoPtr->worldId = worldId;

    //printf("criaMundo worldId worldId.index1: %d\n",worldId.index1);

    mundoPtr->qntd_robos_esq=QNTD_ROBOS_ESQ;
    mundoPtr->qntd_robos_drt=QNTD_ROBOS_DRT;
    mundoPtr->qntd_robos_total=QNTD_ROBOS_TOTAL;

    ///////////Fazer os elementos do nosso mundo
    //Fazer arena
    Arena *arenaPtr = criaArena(mundoPtr);
    mundoPtr->arena = arenaPtr;

    //Fazer robôs
    mundoPtr->robos = malloc(sizeof(Robo*)*QNTD_ROBOS_TOTAL);
    for(int roboId=0;roboId<QNTD_ROBOS_TOTAL;roboId++){
        Robo *roboPtr = criaRobo(mundoPtr);
        roboPtr->time = roboId>=QNTD_ROBOS_ESQ;
        roboPtr->roboId = roboId;
        mundoPtr->robos[roboId]=roboPtr;

        int esq = 1-2*roboPtr->time;
        float amount;
        if(roboPtr->time==0) amount = (float)(roboId)/(QNTD_ROBOS_ESQ-1);
        else                amount = (float)(roboId-QNTD_ROBOS_ESQ)/(QNTD_ROBOS_DRT-1);
        b3Pos posRobo = (b3Pos){
            POSICAO_BOLA_BL.x*esq,
            POSICAO_ROBO_EXTERNO.y,
            Lerp(POSICAO_BOLA_BL.z, -POSICAO_BOLA_BL.z, amount),
        };
        printf("criaMundo posRobo: (x=%f, y=%f, z=%f)",posRobo.x,posRobo.y,posRobo.z);
        b3Body_SetTransform(roboPtr->bodyId, posRobo, b3Quat_identity);
    }

    //Fazer bolas
    mundoPtr->bolas = malloc(sizeof(Bola*)*QNTD_BOLAS);
    for(int bolaId=0;bolaId<QNTD_BOLAS;bolaId++){
        Bola *bolaPtr = criaBola(mundoPtr);
        bolaPtr->bolaId = bolaId;
        mundoPtr->bolas[bolaId] = bolaPtr;
    }

    return mundoPtr;
}