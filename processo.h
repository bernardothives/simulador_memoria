// Arquivo: processo.h
#ifndef PROCESSO_H
#define PROCESSO_H
#include "config.h" // Incluir para ter acesso a MAX_PROCESSOS

// Estrutura que representa um processo no sistema.
typedef struct {
    int pid;
    int tamanho_logico;
    int num_paginas;
    int* tabela_paginas;
} Processo;

// CORREÇÃO: A declaração extern precisa corresponder à definição.
// Agora declara um vetor de ponteiros.
extern Processo* lista_de_processos[MAX_PROCESSOS];

// Funções para gerenciamento de processos
int criar_processo(int pid, int tamanho_processo);
void visualizar_tabela_paginas(int pid);
void destruir_processo(int pid);

#endif // PROCESSO_H