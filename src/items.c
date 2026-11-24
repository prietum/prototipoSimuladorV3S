#include "box3d/id.h"
#include "box3d/math_functions.h"
#include <config.h>

#include <stdio.h>
#include <stdlib.h>

#include <box3d/box3d.h>
#include <items.h>

float lerp(float a, float b, float t){
    return a+(b-a)*t;
}

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
    shapeDef.baseMaterial.friction = 0.1;
    shapeDef.userData = (void*)arenaPtr;
    b3CreateHullShape(bodyId, &shapeDef, &boxHull.base);

    return bodyId;
}

Arena *criaArena(Mundo *mundoPtr){
    printf("criaArena\n");
    
    Arena *arenaPtr = malloc(sizeof(Arena));
    Arena arena = *arenaPtr;

    b3BodyId bodyId_chao = criaParede(mundoPtr,arenaPtr,POSICAO_CHAO,DMNS_CHAO);

    b3BodyId bodyId_parede_lateralN = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_LATERAL_NORTE, DMNS_PAREDE_LATERAL);
    b3BodyId bodyId_parede_lateralS = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_LATERAL_SUL, DMNS_PAREDE_LATERAL);

    b3BodyId bodyId_parede_fundoEsqN = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_FUNDO_ESQ_NORTE,DMNS_PAREDE_FUNDO);
    b3BodyId bodyId_parede_fundoEsqS = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_FUNDO_ESQ_SUL,DMNS_PAREDE_FUNDO);
    b3BodyId bodyId_parede_fundoDrtN = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_FUNDO_DRT_NORTE,DMNS_PAREDE_FUNDO);
    b3BodyId bodyId_parede_fundoDrtS = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_FUNDO_DRT_SUL,DMNS_PAREDE_FUNDO);

    b3BodyId bodyId_parede_traveEsqN = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_TRAVE_ESQ_NORTE,DMNS_PAREDE_TRAVE);
    b3BodyId bodyId_parede_traveEsqS = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_TRAVE_ESQ_SUL,DMNS_PAREDE_TRAVE);
    b3BodyId bodyId_parede_traveDrtN = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_TRAVE_DRT_NORTE,DMNS_PAREDE_TRAVE);
    b3BodyId bodyId_parede_traveDrtS = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_TRAVE_DRT_SUL,DMNS_PAREDE_TRAVE);

    b3BodyId bodyId_parede_golEsq = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_GOL_ESQ,DMNS_PAREDE_GOL);
    b3BodyId bodyId_parede_golDrt = criaParede(mundoPtr, arenaPtr, POSICAO_PAREDE_GOL_DRT,DMNS_PAREDE_GOL);
    
    arenaPtr->tipo.tipo = 1;
    arenaPtr->bodyId_chao = bodyId_chao;
    arenaPtr->bodyId_parede_lateralN = bodyId_parede_lateralN;
    arenaPtr->bodyId_parede_lateralS = bodyId_parede_lateralS;
    arenaPtr->bodyId_parede_fundoEsqN = bodyId_parede_fundoEsqN;
    arenaPtr->bodyId_parede_fundoEsqS = bodyId_parede_fundoEsqS;
    arenaPtr->bodyId_parede_fundoDrtN = bodyId_parede_fundoDrtN;
    arenaPtr->bodyId_parede_fundoDrtS = bodyId_parede_fundoDrtS;
    arenaPtr->bodyId_parede_traveEsqN = bodyId_parede_traveEsqN;
    arenaPtr->bodyId_parede_traveEsqS = bodyId_parede_traveEsqS;
    arenaPtr->bodyId_parede_traveDrtN = bodyId_parede_traveDrtN;
    arenaPtr->bodyId_parede_traveDrtS = bodyId_parede_traveDrtS;
    arenaPtr->bodyId_parede_golEsq = bodyId_parede_golEsq;
    arenaPtr->bodyId_parede_golDrt = bodyId_parede_golDrt;

    return arenaPtr;
}

Roda *criaRoda(Mundo *mundoPtr, Robo *roboPtr, int esq){
    printf("criaRoda\n");
    Roda *rodaPtr = malloc(sizeof(Roda));

    //b3Pos posRobo = b3Body_GetPosition(roboPtr->bodyId);
    b3Pos offRoda;
    b3Quat oriJunta;
    if(esq){
        offRoda=DESLOCAMENTO_RODA_ESQ;
        oriJunta=ORIENTACAO_JUNTA_ESQ;
    }
    else {
        offRoda=DESLOCAMENTO_RODA_DRT;
        oriJunta=ORIENTACAO_JUNTA_DRT;
    }
    b3Pos posRoda = b3Body_GetWorldPoint(roboPtr->bodyId,offRoda);

    b3BodyDef bodyDef = b3DefaultBodyDef();
    bodyDef.type = b3_dynamicBody;
    bodyDef.position = posRoda;
    b3BodyId bodyId = b3CreateBody(mundoPtr->worldId, &bodyDef);

    b3HullData *cylHull = b3CreateCylinder(LARGURA_RODA, RAIO_RODA, LARGURA_RODA/2, 20);
    b3ShapeDef shapeDef = b3DefaultShapeDef();
    shapeDef.userData = (void*)rodaPtr;
    shapeDef.baseMaterial.friction=0.5;
    shapeDef.density = MASSA_RODA/cylHull->volume;
    b3CreateHullShape(bodyId, &shapeDef, cylHull);

    //printf("criaRoda mundoPtr->worldId: %d\n",mundoPtr->worldId.index1);
    //printf("criaRoda roboPtr->bodyId.world0: %d\n",roboPtr->bodyId.world0);
    //printf("criaRoda bodyId.world0: %d\n",bodyId.world0);
    b3WheelJointDef jointDef = b3DefaultWheelJointDef();
    jointDef.base.collideConnected = false;
    jointDef.base.bodyIdA = roboPtr->bodyId;
    jointDef.base.bodyIdB = bodyId;
    jointDef.base.localFrameA = 
        (b3Transform){(b3Vec3)offRoda,b3Quat_identity};
    jointDef.base.localFrameB = 
        (b3Transform){(b3Vec3){0,0,0},oriJunta};
    jointDef.enableSuspensionLimit = true;
    jointDef.lowerSuspensionLimit = 0;
    jointDef.upperSuspensionLimit = 0;
    jointDef.enableSteeringLimit = true;
    jointDef.lowerSteeringLimit = 0;
    jointDef.upperSteeringLimit = 0;
    jointDef.maxSpinTorque = TORQUE_RODA;
    b3JointId jointId = b3CreateWheelJoint(mundoPtr->worldId, &jointDef);
    b3WheelJoint_EnableSpinMotor(jointId, true);

    rodaPtr->tipo.tipo = 3;
    rodaPtr->bodyId = bodyId;
    rodaPtr->jointId = jointId;
    rodaPtr->comando = 0;
    rodaPtr->esq = esq;
    rodaPtr->raio = RAIO_RODA;
    rodaPtr->largura = LARGURA_RODA;

    return rodaPtr;
}

void moveRobo(Robo *roboPtr, b3Pos posicao, b3Quat rotacao){
    b3Body_SetTransform(
        roboPtr->bodyId, 
        posicao, 
        rotacao
    );

    b3Body_SetTransform(
        roboPtr->roda_esq->bodyId, 
        b3Body_GetWorldPoint(
            roboPtr->bodyId, 
            DESLOCAMENTO_RODA_ESQ), 
        b3Quat_identity
    );

    b3Body_SetTransform(
        roboPtr->roda_drt->bodyId, 
        b3Body_GetWorldPoint(
            roboPtr->bodyId, 
            DESLOCAMENTO_RODA_DRT), 
        b3Quat_identity
    );
}

Robo *criaRobo(Mundo *mundoPtr){
    printf("criaRobo\n");
    
    Robo *roboPtr = malloc(sizeof(Robo));

    b3BodyDef bodyDef = b3DefaultBodyDef();
    bodyDef.type = b3_dynamicBody;
    bodyDef.position = (b3Pos){ORIGEM.x, ORIGEM.y, ORIGEM.z};
    //bodyDef.rotation = b3MakeQuatFromAxisAngle((b3Vec3){0,1.0f,0}, 1.57);
    b3BodyId bodyId = b3CreateBody(mundoPtr->worldId,&bodyDef);

    b3BoxHull boxHull = b3MakeBoxHull(DMNS_ROBO/2, DMNS_ROBO/2, DMNS_ROBO/2);
    b3ShapeDef shapeDef = b3DefaultShapeDef();
    shapeDef.density = MASSA_ROBO / boxHull.base.volume;
    shapeDef.baseMaterial.friction = 0.1;
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
        int numerador, denominador;
        float amount;
        if(roboPtr->time==0){
            numerador = roboId+1;
            denominador = QNTD_ROBOS_ESQ+1;
        }else{
            numerador = roboId - QNTD_ROBOS_ESQ+1;
            denominador = QNTD_ROBOS_DRT+1;
        }
        amount = (float) numerador/denominador;

        b3Pos posRobo = (b3Pos){
            POSICAO_BOLA_BL.x*esq,
            POSICAO_ROBO_EXTERNO.y,
            lerp(POSICAO_BOLA_BL.z, -POSICAO_BOLA_BL.z, amount),
        };
        b3Quat rotRobo = b3MakeQuatFromAxisAngle((b3Vec3){0,1,0}, 3.14*(1-roboPtr->time));
        moveRobo(roboPtr, posRobo, rotRobo);
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