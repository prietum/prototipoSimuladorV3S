#include <gui.h>

void criaJanela(){
    InitWindow(600,600,"Prototipo3D");
    SetTargetFPS(60);
}

void destroiJanela(){
    CloseWindow();
}