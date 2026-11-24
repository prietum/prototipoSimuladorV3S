////////////////// INICIALIZAÇÃO DA PARTIDA
#define QNTD_ROBOS_ESQ (3)
#define QNTD_ROBOS_DRT (3)
#define QNTD_ROBOS_TOTAL (QNTD_ROBOS_ESQ+QNTD_ROBOS_DRT)
#define QNTD_BOLAS (1)

////////////////// MEDIDAS SI
#define MILIMETROS (1.0f/1000)
#define CENTIMETROS (1.0f/100)
#define QUILOGRAMAS (1.0f)
#define GRAMAS (1.0f/1000)
#define KGCM (QUILOGRAMAS*CENTIMETROS) //torque
#define RPM (6.28f/60.0f) //converte para radianos/segundo ao multiplicar

////////////////// ESPECIFICAÇÕES DO ROBÔ
#define MASSA_ROBO (500.0f * GRAMAS)
#define DMNS_ROBO (75.0f * MILIMETROS)
#define ALTURA_ASSOALHO (5.0f * MILIMETROS) //espaço entre o contato da roda com o chão e o fundo da carcaça do robô

////////////////// ESPECIFICAÇÕES DA RODA DO ROBÔ
#define MASSA_RODA (100.0f * GRAMAS)
#define RAIO_RODA (15.0f * MILIMETROS)
#define LARGURA_RODA (10.0f * MILIMETROS)
#define PROFUNDIDADE_RODA ((LARGURA_RODA/2)) //quantos milimetros para dentro fica a roda?
#define DESLOCAMENTO_RODA_ESQ (                    \
    (b3Pos){                                       \
        0,                                         \
        -DMNS_ROBO/2 + RAIO_RODA - ALTURA_ASSOALHO,\
        (DMNS_ROBO/2 - PROFUNDIDADE_RODA)* 1       \
    }                                              \
)
#define ORIENTACAO_JUNTA_ESQ (                    \
    b3MulQuat(                                         \
        b3MakeQuatFromAxisAngle((b3Vec3){1,0,0}, 1.57),\
        b3MakeQuatFromAxisAngle((b3Vec3){0,1,0}, 3.14) \
    )                                                  \
)
#define DESLOCAMENTO_RODA_DRT (                    \
    (b3Pos){                                       \
        0,                                         \
        -DMNS_ROBO/2 + RAIO_RODA - ALTURA_ASSOALHO,\
        (DMNS_ROBO/2 - PROFUNDIDADE_RODA)*-1       \
    }                                              \
)
#define ORIENTACAO_JUNTA_DRT (                    \
    b3MulQuat(                                         \
        b3MakeQuatFromAxisAngle((b3Vec3){1,0,0}, 1.57),\
        b3MakeQuatFromAxisAngle((b3Vec3){0,1,0}, 0.00) \
    )                                                  \
)
#define TORQUE_RODA (0.86f*KGCM)
#define RPM_RODA (500.0f*RPM)

////////////////// ESPECIFICAÇÕES DA BOLA
#define RAIO_BOLA (32.7f * MILIMETROS)
#define MASSA_BOLA (200.0f * GRAMAS)

////////////////// ESPECIFICAÇÕES DA ARENA
//medidas
#define LARGURA_PAREDE (2.5f * CENTIMETROS)
#define ALTURA_PAREDE (8.0f * CENTIMETROS)

#define COMPRIMENTO_ARENA (150.0f * CENTIMETROS)
#define LARGURA_ARENA (130.0f * CENTIMETROS)

#define PROFUNDIDADE_GOL (8.0f * CENTIMETROS)
#define LARGURA_GOL (50.0f * CENTIMETROS)
#define LARGURA_FUNDO ((LARGURA_ARENA - LARGURA_GOL)/2)

//dimensões (volume)
#define DMNS_CHAO ((b3Vec3){COMPRIMENTO_ARENA+LARGURA_PAREDE*4+PROFUNDIDADE_GOL*2, LARGURA_PAREDE, LARGURA_ARENA})
#define DMNS_PAREDE_LATERAL ((b3Vec3){COMPRIMENTO_ARENA, ALTURA_PAREDE, LARGURA_PAREDE})
#define DMNS_PAREDE_FUNDO ((b3Vec3){LARGURA_PAREDE, ALTURA_PAREDE, LARGURA_FUNDO})
#define DMNS_PAREDE_TRAVE ((b3Vec3){PROFUNDIDADE_GOL, ALTURA_PAREDE, LARGURA_PAREDE})
#define DMNS_PAREDE_GOL ((b3Vec3){LARGURA_PAREDE, ALTURA_PAREDE, LARGURA_GOL+LARGURA_PAREDE*4})

//eixos, basta mudar o sinal para trocar norte/sul, direita/esquerda
#define X_LATERAL (0)
#define X_FUNDO (COMPRIMENTO_ARENA/2+LARGURA_PAREDE/2)
#define X_TRAVE (COMPRIMENTO_ARENA/2+PROFUNDIDADE_GOL/2+LARGURA_PAREDE)
#define X_GOL (COMPRIMENTO_ARENA/2+PROFUNDIDADE_GOL+LARGURA_PAREDE*1.5)

#define Y_CHAO (0)
#define Y_PAREDE (ALTURA_PAREDE/2)

#define Z_LATERAL (LARGURA_ARENA/2 + LARGURA_PAREDE/2)
#define Z_FUNDO (LARGURA_ARENA/2 - LARGURA_FUNDO/2 + LARGURA_PAREDE)
#define Z_TRAVE (LARGURA_ARENA/2 - LARGURA_FUNDO + LARGURA_PAREDE*1.5)
#define Z_GOL (0)

//posições, usamos os eixos pois a arena é simétrica
#define ORIGEM ((b3Pos){0.0f,0.0f,0.0f})
#define POSICAO_CHAO ((b3Pos){\
    ORIGEM.x+0,     \
    ORIGEM.y+Y_CHAO,\
    ORIGEM.z+0      \
})
#define POSICAO_PAREDE_LATERAL_NORTE ((b3Pos){\
    ORIGEM.x+X_LATERAL,\
    ORIGEM.y+Y_PAREDE, \
    ORIGEM.z-Z_LATERAL \
})
#define POSICAO_PAREDE_LATERAL_SUL ((b3Pos){\
    ORIGEM.x+X_LATERAL,\
    ORIGEM.y+Y_PAREDE, \
    ORIGEM.z+Z_LATERAL \
})
#define POSICAO_PAREDE_FUNDO_ESQ_NORTE ((b3Pos){\
    ORIGEM.x-X_FUNDO, \
    ORIGEM.y+Y_PAREDE,\
    ORIGEM.z-Z_FUNDO  \
})
#define POSICAO_PAREDE_FUNDO_ESQ_SUL ((b3Pos){\
    ORIGEM.x-X_FUNDO, \
    ORIGEM.y+Y_PAREDE,\
    ORIGEM.z+Z_FUNDO  \
})
#define POSICAO_PAREDE_FUNDO_DRT_NORTE ((b3Pos){\
    ORIGEM.x+X_FUNDO, \
    ORIGEM.y+Y_PAREDE,\
    ORIGEM.z-Z_FUNDO  \
})
#define POSICAO_PAREDE_FUNDO_DRT_SUL ((b3Pos){\
    ORIGEM.x+X_FUNDO, \
    ORIGEM.y+Y_PAREDE,\
    ORIGEM.z+Z_FUNDO  \
})
#define POSICAO_PAREDE_TRAVE_ESQ_NORTE ((b3Pos){\
    ORIGEM.x-X_TRAVE, \
    ORIGEM.y+Y_PAREDE,\
    ORIGEM.z-Z_TRAVE  \
})
#define POSICAO_PAREDE_TRAVE_ESQ_SUL ((b3Pos){\
    ORIGEM.x-X_TRAVE, \
    ORIGEM.y+Y_PAREDE,\
    ORIGEM.z+Z_TRAVE  \
})
#define POSICAO_PAREDE_TRAVE_DRT_NORTE ((b3Pos){\
    ORIGEM.x+X_TRAVE, \
    ORIGEM.y+Y_PAREDE,\
    ORIGEM.z-Z_TRAVE  \
})
#define POSICAO_PAREDE_TRAVE_DRT_SUL ((b3Pos){\
    ORIGEM.x+X_TRAVE, \
    ORIGEM.y+Y_PAREDE,\
    ORIGEM.z+Z_TRAVE  \
})
#define POSICAO_PAREDE_GOL_ESQ ((b3Pos){\
    ORIGEM.x-X_GOL,   \
    ORIGEM.y+Y_PAREDE,\
    ORIGEM.z+Z_GOL    \
})
#define POSICAO_PAREDE_GOL_DRT ((b3Pos){\
    ORIGEM.x+X_GOL,   \
    ORIGEM.y+Y_PAREDE,\
    ORIGEM.z+Z_GOL    \
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
    ORIGEM.y + DMNS_ROBO/2 + ALTURA_ASSOALHO,         \
    ORIGEM.z - 25.0f*CENTIMETROS                      \
})

#define POSICAO_ROBO_EXTERNO ((b3Pos){                \
    ORIGEM.x - 37.5f*CENTIMETROS - 20.0f*CENTIMETROS, \
    ORIGEM.y + DMNS_ROBO/2 + ALTURA_ASSOALHO,         \
    ORIGEM.z - 25.0f*CENTIMETROS                      \
})

////////////////// INTERFACE GRÁFICA
#define POSICAO_CAMERA ((Vector3){0.0f,6.0f,0.1f})
#define COMPRIMENTO_JANELA (600)
#define ALTURA_JANELA (600)

//////////////////