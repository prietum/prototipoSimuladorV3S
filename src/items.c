#include "box3d/collision.h"
#include "box3d/id.h"
#include "box3d/math_functions.h"
#include "box3d/types.h"
#include "raylib.h"
#include <config.h>

#include <stdio.h>
#include <stdlib.h>

#include <box3d/box3d.h>
#include <items.h>

b3BodyId criaParede(Mundo *mundoPtr, b3Vec3 pos, b3Vec3 size){
    Mundo mundo = *mundoPtr;
    b3Vec3 offpos = {pos.x-size.x/2,pos.y-size.y/2,pos.z/size.z/2};

    b3BodyDef bodyDef = b3DefaultBodyDef();
    bodyDef.position = (b3Pos)offpos;
    bodyDef.type = b3_staticBody;
    b3BodyId bodyId = b3CreateBody(mundo.worldId, &bodyDef);

    //...

    return bodyId;
}

Arena *criaArena(Mundo *mundoPtr){
    Mundo mundo = *mundoPtr;
    Arena *arenaPtr = malloc(sizeof(Arena));
    Arena arena = *arenaPtr;
    
    //...

    return arenaPtr;
}

Roda *criaRoda(Mundo *mundoPtr, Robo *roboPtr, int esq){
    Mundo mundo = *mundoPtr;
    Robo robo = *roboPtr;
    Roda *rodaPtr = malloc(sizeof(Roda));
    Roda roda = *rodaPtr;

    b3Vec3 offset;
    if (esq)
        offset = (b3Vec3){
        DMNS_ROBO/2 + PROFUNDIDADE_RODA,
        -DMNS_ROBO/2 + RAIO_RODA - ALTURA_RODA,
        0.0f
        };
    else
        offset = (b3Vec3){
        -(DMNS_ROBO/2 + PROFUNDIDADE_RODA),
        -DMNS_ROBO/2 + RAIO_RODA - ALTURA_RODA,
        0.0f
        };

    b3BodyDef bodyDef = b3DefaultBodyDef();
    bodyDef.type = b3_dynamicBody;
    bodyDef.position = (b3Pos) offset;
    b3BodyId bodyId = b3CreateBody(mundo.worldId, &bodyDef);

    b3HullData *cylHull = b3CreateCylinder(LARGURA_RODA, RAIO_RODA, LARGURA_RODA/2, 20);
    b3ShapeDef shapeDef = b3DefaultShapeDef();
    b3CreateHullShape(bodyId, &shapeDef, cylHull);

    b3MotorJointDef jointDef = b3DefaultMotorJointDef();
    jointDef.base.bodyIdA = robo.bodyId;
    jointDef.base.bodyIdB = bodyId;
    jointDef.base.localFrameA = b3Transform_identity;
    jointDef.base.localFrameB = b3Transform_identity;
    b3JointId jointId = b3CreateMotorJoint(mundo.worldId, &jointDef);

    roda.bodyId = bodyId;
    roda.jointId = jointId;
    roda.comando = 0;
    roda.esq = esq;
    roda.raio = RAIO_RODA;
    roda.largura = LARGURA_RODA;

    return rodaPtr;
}

Robo *criaRobo(Mundo *mundoPtr){
    Mundo mundo = *mundoPtr;
    Robo *roboPtr = malloc(sizeof(Robo));
    Robo robo = *roboPtr;

    b3BodyDef bodyDef = b3DefaultBodyDef();
    bodyDef.type = b3_dynamicBody;
    bodyDef.position = (b3Vec3){0.0f,0.0f,0.0f};
    b3BodyId bodyId = b3CreateBody(mundo.worldId,&bodyDef);

    b3BoxHull boxHull = b3MakeBoxHull(DMNS_ROBO/2, DMNS_ROBO/2, DMNS_ROBO/2);
    b3ShapeDef shapeDef = b3DefaultShapeDef();
    b3CreateHullShape(bodyId, &shapeDef, &boxHull.base);

    robo.bodyId = bodyId;
    robo.dmns = DMNS_ROBO;
    robo.roda_drt = criaRoda(mundoPtr, roboPtr, 0);
    robo.roda_esq = criaRoda(mundoPtr, roboPtr, 1);

    return roboPtr;
}

Bola *criaBola(Mundo *mundoPtr){
    Mundo mundo = *mundoPtr;
    Bola *bolaPtr = malloc(sizeof(Bola));
    Bola bola = *bolaPtr;

    b3BodyDef bodyDef = b3DefaultBodyDef();
    bodyDef.type = b3_dynamicBody;
    bodyDef.position = (b3Vec3){0.0f,0.0f,0.0f};
    b3BodyId bodyId = b3CreateBody(mundo.worldId, &bodyDef);

    b3Sphere sphere = {.center = 0, .radius = RAIO_BOLA};
    b3ShapeDef shapeDef = b3DefaultShapeDef();
    b3CreateSphereShape(bodyId, &shapeDef, &sphere);

    bola.raio = RAIO_BOLA;
    bola.bodyId = bodyId;

    return bolaPtr;
}

Mundo *criaMundo(
    void *(*criaDebugShape)(const b3DebugShape *debugShape, void *context),
    void (*destroiDebugShape)(void *userShape, void *context))
{
    ///////////Fazer o mundo em si
    Mundo *mundoPtr = malloc(sizeof(Mundo));
    Mundo mundo = *mundoPtr;

    b3WorldDef worldDef = b3DefaultWorldDef();
    worldDef.gravity = (b3Vec3){0.0f,9.8f,0.0f};
    worldDef.createDebugShape = criaDebugShape;
    worldDef.destroyDebugShape = destroiDebugShape;

    b3WorldId worldId = b3CreateWorld(&worldDef);
    mundo.worldId = worldId;

    mundo.qntd_robos_esq=QNTD_ROBOS_ESQ;
    mundo.qntd_robos_drt=QNTD_ROBOS_DRT;
    mundo.qntd_robos_total=QNTD_ROBOS_TOTAL;

    ///////////Fazer os elementos do nosso mundo
    //Fazer arena
    Arena *arenaPtr = criaArena(mundoPtr);
    mundo.arena = arenaPtr;

    //Fazer robôs
    for(int roboId=0;roboId<QNTD_ROBOS_TOTAL;roboId++){
        Robo *roboPtr = criaRobo(mundoPtr);
        Robo robo = *roboPtr;
        robo.time = roboId>=QNTD_ROBOS_ESQ;
        robo.roboId = roboId;
        mundo.robos[roboId]=robo;
    }

    //Fazer bolas
    for(int bolaId=0;bolaId<QNTD_BOLAS;bolaId++){
        Bola *bolaPtr = criaBola(mundoPtr);
        Bola bola = *bolaPtr;
        bola.bolaId = bolaId;
        mundo.bolas[bolaId] = bola;
    }

    return mundoPtr;
}