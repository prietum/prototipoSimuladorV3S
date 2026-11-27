//////////////// POSIÇÕES FIXAS
#define POSICAO_PANORAMICA ((Vector3){0.0f,6.0f,0.1f})
#define POSICAO_GOLEIRO_ESQ ((Vector3){0.0f,6.0f,0.1f})
#define POSICAO_GOLEIRO_DRT ((Vector3){0.0f,6.0f,0.1f})
#define POSICAO_LATERAL_NORTE ((Vector3){0.0f,6.0f,0.1f})
#define POSICAO_LATERAL_SUL ((Vector3){0.0f,6.0f,0.1f})
#define POSICAO_FUNDO_ESQ_NORTE ((Vector3){0.0f,6.0f,0.1f})
#define POSICAO_FUNDO_ESQ_SUL ((Vector3){0.0f,6.0f,0.1f})
#define POSICAO_FUNDO_DRT_NORTE ((Vector3){0.0f,6.0f,0.1f})
#define POSICAO_FUNDO_DRT_SUL ((Vector3){0.0f,6.0f,0.1f})
#define POSICAO_PENALTI_ESQ ((Vector3){0.0f,6.0f,0.1f})
#define POSICAO_PENALTI_DRT ((Vector3){0.0f,6.0f,0.1f})
/*
    00    - Panorâmica, olha a arena do topo. Fica alinhada com o norte (-Z).
    01~08 - Posições de espectador, olham a arena da arquibancada.
    09~10 - Posições de pênalti, olham para o gol a partir do ponto CP.
*/
#define VETOR_POSICOES ({\
    POSICAO_PANORAMICA,\
    \
    POSICAO_GOLEIRO_ESQ,\
    POSICAO_FUNDO_ESQ_NORTE,\
    POSICAO_LATERAL_NORTE,\
    POSICAO_FUNDO_DRT_NORTE,\
    POSICAO_GOLEIRO_DRT,\
    POSICAO_FUNDO_DRT_SUL,\
    POSICAO_LATERAL_SUL,\
    POSICAO_FUNDO_ESQ_SUL,\
    \
    POSICAO_PENALTI_ESQ,\
    POSICAO_PENALTI_DRT\
})