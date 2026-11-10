////////////////// PARTIDA
#define QNTD_ROBOS_ESQ (2)
#define QNTD_ROBOS_DRT (2)
#define QNTD_ROBOS_TOTAL (QNTD_ROBOS_ESQ+QNTD_ROBOS_DRT)
#define QNTD_BOLAS (1)

////////////////// MEDIDAS
#define MILIMETROS (1.0f/1000)
#define CENTIMETROS (1.0f/100)
#define GRAMAS (1.0f/1000)

//especificações do robô
#define TORQUE (1.0f)
#define MASS_ROBO (500.0f * GRAMAS)
#define DMNS_ROBO (75.0f * MILIMETROS)
#define RAIO_RODA (10.0f * MILIMETROS)
#define ALTURA_RODA (3.0f * MILIMETROS) //espaço entre o contato da roda com o chão e o fundo da carcaça do robô
#define LARGURA_RODA (10.0f * MILIMETROS)
#define PROFUNDIDADE_RODA ((LARGURA_RODA/2)) //quantos milimetros para dentro fica a roda?

//especificações da bola
#define RAIO_BOLA (32.7f * MILIMETROS)
#define MASSA_BOLA (200.0f * GRAMAS)

//especificações da arena (conforme VSSS)
#define LARGURA_ARENA (130.0f * CENTIMETROS)
#define COMPRIMENTO_ARENA (150.0f * CENTIMETROS)
#define PROFUNDIDADE_GOL (8.0f * CENTIMETROS)
#define LARGURA_GOL (50.0f * CENTIMETROS)
#define LARGURA_PAREDES (2.5f * CENTIMETROS)
#define ALTURA_PAREDES (8.0f * CENTIMETROS)

////////////////// INTERFACE
#define COMPRIMENTO_JANELA (600)
#define ALTURA_JANELA (600)

//////////////////