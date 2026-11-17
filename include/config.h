////////////////// INICIALIZAÇÃO DA PARTIDA
#define QNTD_ROBOS_ESQ (6)
#define QNTD_ROBOS_DRT (2)
#define QNTD_ROBOS_TOTAL (QNTD_ROBOS_ESQ+QNTD_ROBOS_DRT)
#define QNTD_BOLAS (1)

////////////////// MEDIDAS SI
#define MILIMETROS (1.0f/1000)
#define CENTIMETROS (1.0f/100)
#define GRAMAS (1.0f/1000)

////////////////// ESPECIFICAÇÕES DO ROBÔ
#define TORQUE (1.0f)
#define MASS_ROBO (500.0f * GRAMAS)
#define DMNS_ROBO (75.0f * MILIMETROS)
#define RAIO_RODA (10.0f * MILIMETROS)
#define ALTURA_RODA (3.0f * MILIMETROS) //espaço entre o contato da roda com o chão e o fundo da carcaça do robô
#define LARGURA_RODA (10.0f * MILIMETROS)
#define PROFUNDIDADE_RODA ((LARGURA_RODA/2)) //quantos milimetros para dentro fica a roda?

////////////////// ESPECIFICAÇÕES DA BOLA
#define RAIO_BOLA (32.7f * MILIMETROS)
#define MASSA_BOLA (200.0f * GRAMAS)

////////////////// ESPECIFICAÇÕES DA ARENA
#define LARGURA_PAREDE (2.5f * CENTIMETROS)
#define ALTURA_PAREDE (8.0f * CENTIMETROS)

#define COMPRIMENTO_ARENA (150.0f * CENTIMETROS)
#define LARGURA_ARENA (130.0f * CENTIMETROS)

#define PROFUNDIDADE_GOL (8.0f * CENTIMETROS)
#define LARGURA_GOL (50.0f * CENTIMETROS)

#define DMNS_CHAO ((b3Vec3){COMPRIMENTO_ARENA, LARGURA_PAREDE, LARGURA_ARENA})
#define DMNS_PAREDE_LATERAL ((b3Vec3){COMPRIMENTO_ARENA, ALTURA_PAREDE, LARGURA_PAREDE})
#define DMNS_PAREDE_FUNDO ((b3Vec3){LARGURA_PAREDE, ALTURA_PAREDE, LARGURA_ARENA})

#define ORIGEM ((b3Pos){0,0,0})
#define POSICAO_CHAO (ORIGEM)
#define POSICAO_PAREDE_CIMA ((b3Pos){              \
    ORIGEM.x,                                      \
    ORIGEM.y+ALTURA_PAREDE/2+LARGURA_PAREDE/2,     \
    ORIGEM.z-LARGURA_ARENA/2-LARGURA_PAREDE/2      \
})
#define POSICAO_PAREDE_BAIXO ((b3Pos){             \
    ORIGEM.x,                                      \
    ORIGEM.y+ALTURA_PAREDE/2+LARGURA_PAREDE/2,     \
    ORIGEM.z+LARGURA_ARENA/2+LARGURA_PAREDE/2      \
})
#define POSICAO_PAREDE_ESQUERDA ((b3Pos){          \
    ORIGEM.x-COMPRIMENTO_ARENA/2-LARGURA_PAREDE/2, \
    ORIGEM.y+ALTURA_PAREDE/2+LARGURA_PAREDE/2,     \
    ORIGEM.z                                       \
})
#define POSICAO_PAREDE_DIREITA ((b3Pos){           \
    ORIGEM.x+COMPRIMENTO_ARENA/2+LARGURA_PAREDE/2, \
    ORIGEM.y+ALTURA_PAREDE/2+LARGURA_PAREDE/2,     \
    ORIGEM.z                                       \
})

////////////////// ESPECIFICAÇÕES POSICIONAMENTO DOS ROBÔS
//Ao usar, basta inverter os sinais de x e/ou y para obter os demais pontos, já que o campo é simétrico em ambos os eixos!
//BL: Bola livre
//TL: Tiro livre
//CP: Cobrança de pênalti
//Existem 8 posições que o robô admite em qualquer uma dessas situações. 4 externas, 4 internas.
#define POSICAO_BOLA_INICIO ((b3Pos){ \
    ORIGEM.x,                     \
    ORIGEM.y + RAIO_BOLA/2,       \
    ORIGEM.z                      \
})
#define POSICAO_BOLA_BL ((b3Pos){ \
    ORIGEM.x - 37.5f*CENTIMETROS, \
    ORIGEM.y + RAIO_BOLA/2,       \
    ORIGEM.z - 40.0f*CENTIMETROS  \
})
#define POSICAO_BOLA_TL ((b3Pos){ \
    ORIGEM.x - 37.5f*CENTIMETROS, \
    ORIGEM.y + RAIO_BOLA/2,       \
    ORIGEM.z                      \
})
#define POSICAO_BOLA_CP (POSICAO_BOLA_TL)

#define POSICAO_ROBO_INTERNO ((b3Pos){                \
    ORIGEM.x - 37.5f*CENTIMETROS + 20.0f*CENTIMETROS, \
    ORIGEM.y + DMNS_ROBO/2,                           \
    ORIGEM.z - 25.0f*CENTIMETROS                      \
})

#define POSICAO_ROBO_EXTERNO ((b3Pos){                \
    ORIGEM.x - 37.5f*CENTIMETROS - 20.0f*CENTIMETROS, \
    ORIGEM.y + DMNS_ROBO/2,                           \
    ORIGEM.z - 25.0f*CENTIMETROS                      \
})

////////////////// INTERFACE GRÁFICA
#define COMPRIMENTO_JANELA (600)
#define ALTURA_JANELA (600)

//////////////////