#include <sim.h>
#include <gui.h>

void syncSimulacaoComJanela(){
    while(gui_janelaAberta()){
        float dt = gui_passo();
        sim_passo(dt);
    }
}

int main(){
    gui_criaJanela();
    sim_criaSimulacao();
    syncSimulacaoComJanela();

    gui_destroiJanela();
    sim_destroiSimulacao();
    
    return 0;
}