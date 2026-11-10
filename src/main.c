#include <config.h>

#include <stdio.h>
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
    UserShape* minhaShapePtr = (UserShape*)userShape;
    UserShape  minhaShape = *minhaShapePtr;

    Vector3 position = (Vector3){transform.p.x,transform.p.y,transform.p.z};
    if(strcmp(minhaShape.tipo,"caixa") == 0){
        //tamanho da caixa
        Vector3 extents = {minhaShape.extents.x*2,minhaShape.extents.y*2,minhaShape.extents.z*2};

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
        DrawCubeV((Vector3){0,0,0},extents,BLACK);
        rlPopMatrix();
    }else if(strcmp(minhaShape.tipo,"esfera") == 0){
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
        DrawSphere((Vector3){0,0,0},minhaShape.radius,BLACK);
        rlPopMatrix();
    }
}

void *criaDebugShape(const b3DebugShape *debugShape, void *context){
    UserShape *minhaShapePtr = malloc(sizeof(UserShape));
    UserShape minhaShape= *minhaShapePtr;

    if(debugShape->type == b3_hullShape){ //se for uma caixa
        minhaShape.tipo="caixa";
        b3AABB aabb = debugShape->hull->aabb;
        minhaShape.extents.x = (aabb.lowerBound.x-aabb.upperBound.x)*0.5f;
        minhaShape.extents.y = (aabb.lowerBound.y-aabb.upperBound.y)*0.5f;
        minhaShape.extents.z = (aabb.lowerBound.z-aabb.upperBound.z)*0.5f;
    }else if (debugShape->type == b3_sphereShape){ //se for uma esfera
        minhaShape.tipo="esfera";
        minhaShape.radius = debugShape->sphere->radius;
    }

    return (void *) minhaShapePtr;
}

void destroiDebugShape(void *userShape, void *context){
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
        (b3Vec3){-100.0f,-100.0f,-100.0f}
    };

    //cria cameras
    camera = (Camera3D){0};
    camera.position = (Vector3){0.0f,10.0f,0.0f};
    camera.target = (Vector3){0.0f,0.0f,0.0f};
    camera.fovy = 45;
    camera.projection = CAMERA_ORTHOGRAPHIC; //VISÃO ORTOGRÁFICA/'2D'

    //cria mundo
    Mundo *mundoPtr = criaMundo(criaDebugShape, destroiDebugShape);
    Mundo mundo = *mundoPtr;

    //loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        b3World_Step(mundo.worldId, dt, 4);

        BeginDrawing();
        BeginMode3D(camera);
        b3World_Draw(mundo.worldId, &debugDraw, UINT64_MAX);
        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    free(mundoPtr);
    
    return 0;
}