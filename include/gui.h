#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <sim.h>
#include <interface.h>
#include <partida.h>

void  gui_criaJanela();
void  gui_destroiJanela();
float gui_passo();
int   gui_janelaAberta();
void  gui_desenhaMundoOrtografico(Mundo *mundoPtr); //Desenha o mundo de cima para baixo
void  gui_desenhaMundoPerspectiva(Mundo *mundoPtr); //Desenha o mundo da arquibancada
void  gui_desenhaInterface(); //Desenha os botões e afins