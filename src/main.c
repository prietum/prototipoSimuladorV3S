#include <config.h>

//#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

#include <box3d/box3d.h>
#include <items.h>

#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>
#include <rlgl.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

//User Shape
//Nós podemos abstrair uma forma geométrica do Box3D para dentro de uma struct que faça sentido para nós,
//  com dados úteis para nossa aplicação, seja quais forem.
//Essa struct é chamada de User Shape.
//Ela é criada toda vez que vamos desenhar uma forma geométrica nova.
typedef struct {
    char* tipo;
    b3Vec3 extents; //tamanho de uma forma geométrica de caixa, se for o caso
    float radius; //raio de uma forma geométrica de esfera, se for o caso
} UserShape;

Camera3D camera;
b3DebugDraw debugDraw;

void desenha(void *userShape, b3WorldTransform transform, b3HexColor color, void *context){
    //printf("desenha\n");
    UserShape* minhaShapePtr = (UserShape*)userShape;
    Vector3 position = (Vector3){transform.p.x,transform.p.y,transform.p.z};

    // printf("desenha minhaShapePtr->tipo: %s\n", minhaShapePtr->tipo);
    //pegar matriz de rotação da caixa com magia negra
    Matrix mat = QuaternionToMatrix((Quaternion){
        transform.q.v.x,
        transform.q.v.y,
        transform.q.v.z,
        transform.q.s
    });

    //coloca posição dentro da matriz de rotação
    mat.m12 = position.x;
    mat.m13 = position.y;
    mat.m14 = position.z;

    //mais magia negra, empurramos a matriz de posição+rotação na pilha do renderizador
    rlPushMatrix();
    rlMultMatrixf(MatrixToFloat(mat));

    if(strcmp(minhaShapePtr->tipo,"placa") == 0){
        //printf("desenha placa\n");
        //tamanho da caixa
        Vector3 extents = {minhaShapePtr->extents.x*2,minhaShapePtr->extents.y*2,minhaShapePtr->extents.z*2};
        DrawCubeV((Vector3){0,0,0},extents,GRAY);
    }
    else if(strcmp(minhaShapePtr->tipo,"bola") == 0){
        //printf("desenha bola\n");
        DrawSphere((Vector3){0,0,0},minhaShapePtr->radius,ORANGE);
    }
    else if(strcmp(minhaShapePtr->tipo,"roda") == 0){
        //printf("desenha roda\n");
        Vector3 extents = {minhaShapePtr->extents.x,minhaShapePtr->extents.y*2,minhaShapePtr->extents.z};

        DrawCylinder((Vector3){0,0,0},extents.x,extents.z,extents.y,20,GREEN);
    }
    else if(strcmp(minhaShapePtr->tipo,"robo") == 0){
        //printf("desenha robo\n");
        Vector3 extents = {minhaShapePtr->extents.x*2,minhaShapePtr->extents.y*2,minhaShapePtr->extents.z*2};

        DrawCubeV((Vector3){0,0,0},extents,BLUE);
    }

    //tira a matriz do topo da pilha
    rlPopMatrix();
}

void *criaDebugShape(const b3DebugShape *debugShape, void *context){
    //printf("criaDebugShape\n");
    UserShape *minhaShapePtr = malloc(sizeof(UserShape));
    void* userData = b3Shape_GetUserData(debugShape->shapeId);
    Tipo* tipoPtr = (Tipo*)userData;

    if(tipoPtr->tipo==1){
        //printf("criaDebugShape: placa\n");
        Arena* arenaPtr = (Arena*)userData;
        
        minhaShapePtr->tipo="placa";
        b3AABB aabb = debugShape->hull->aabb;
        minhaShapePtr->extents.x = (aabb.upperBound.x-aabb.lowerBound.x)*0.5f;
        minhaShapePtr->extents.y = (aabb.upperBound.y-aabb.lowerBound.y)*0.5f;
        minhaShapePtr->extents.z = (aabb.upperBound.z-aabb.lowerBound.z)*0.5f;
    }
    if(tipoPtr->tipo==2){
        //printf("criaDebugShape: bola\n");
        Bola* bolaPtr = (Bola*)userData;
        
        minhaShapePtr->tipo="bola";
        minhaShapePtr->radius = debugShape->sphere->radius;
    }
    if(tipoPtr->tipo==3){
        printf("criaDebugShape: roda\n");
        Roda* rodaPtr = (Roda*)userData;
        
        minhaShapePtr->tipo="roda";
        b3AABB aabb = debugShape->hull->aabb;
        minhaShapePtr->extents.x = (aabb.upperBound.x-aabb.lowerBound.x)*0.5f;
        minhaShapePtr->extents.y = (aabb.upperBound.y-aabb.lowerBound.y)*0.5f;
        minhaShapePtr->extents.z = (aabb.upperBound.z-aabb.lowerBound.z)*0.5f;
        printf("criaDebugShape: roda extents: %f %f %f\n", minhaShapePtr->extents.x,
minhaShapePtr->extents.y,
minhaShapePtr->extents.z);
    }
    if(tipoPtr->tipo==4){
        //printf("criaDebugShape: robo\n");
        Robo* roboPtr = (Robo*)userData;

        minhaShapePtr->tipo="robo";
        b3AABB aabb = debugShape->hull->aabb;
        minhaShapePtr->extents.x = (aabb.upperBound.x-aabb.lowerBound.x)*0.5f;
        minhaShapePtr->extents.y = (aabb.upperBound.y-aabb.lowerBound.y)*0.5f;
        minhaShapePtr->extents.z = (aabb.upperBound.z-aabb.lowerBound.z)*0.5f;
    }

    return (void *) minhaShapePtr;
}

void destroiDebugShape(void *userShape, void *context){
    //printf("destroiDebugShape\n");
    free(userShape);
}

int main(){
    //cria janela
    InitWindow(600,600,"Prototipo3D");
    SetTargetFPS(60);

    //cria debugDraw
    //é um struct que armazena as funções de callback para renderização
    //a que vamos usar é DrawShapeFcn
    debugDraw = b3DefaultDebugDraw();
    debugDraw.DrawShapeFcn = desenha; //função responsável por desenhar "shapes", formas geométricas
    debugDraw.drawShapes = true; //é pra desenhar?
    debugDraw.drawingBounds = (b3AABB){ //isso aqui é um volume, desenhamos só o que está dentro do volume
        (b3Vec3){-100.0f,-100.0f,-100.0f},
        (b3Vec3){100.0f,100.0f,100.0f}
    };

    //cria cameras
    camera = (Camera3D){0};
    camera.position = POSICAO_CAMERA;
    camera.target = (Vector3){0.0f,0.0f,0.0f};
    camera.up = (Vector3){0.0f,1.0f,0.0f};
    camera.fovy = 20;
    camera.projection = CAMERA_PERSPECTIVE;

    //cria mundo
    Mundo *mundoPtr = criaMundo(criaDebugShape, destroiDebugShape);

    //loop
    printf("Loop principal\n");
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        for(int roboId=0;roboId<QNTD_ROBOS_TOTAL;roboId++){
            b3WheelJoint_SetSpinMotorSpeed(mundoPtr->robos[roboId]->roda_drt->jointId, RPM_RODA);
            b3WheelJoint_SetSpinMotorSpeed(mundoPtr->robos[roboId]->roda_esq->jointId, RPM_RODA);
        }

        b3World_Step(mundoPtr->worldId, dt, 4);

        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                DrawGrid(10, 1.0f);
                b3World_Draw(mundoPtr->worldId, &debugDraw, UINT64_MAX);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    free(mundoPtr);
    
    return 0;
}