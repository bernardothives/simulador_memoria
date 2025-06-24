#ifndef PROCESSO_H
#define PROCESSO_H

// Estrutura que representa um processo no sistema.
// Contém informações essenciais para o gerenciamento de sua memória.
typedef struct {
    int pid;                   // Identificador único do processo.
    int tamanho_logico;        // Tamanho total do espaço de endereçamento lógico em bytes.
    int num_paginas;           // Número de páginas lógicas que o processo ocupa.
    int* tabela_paginas;       // Ponteiro para a tabela de páginas do processo (um vetor de inteiros).
} Processo;

// Vetor global para armazenar ponteiros para os processos ativos.
extern Processo* lista_de_processos;

// Funções para gerenciamento de processos
int criar_processo(int pid, int tamanho_processo);
void visualizar_tabela_paginas(int pid);
void destruir_processo(int pid); // Função para liberar os recursos de um processo

#endif // PROCESSO_H