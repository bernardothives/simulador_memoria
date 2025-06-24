#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "processo.h"
#include "gerenciador_memoria.h"

// Definição da variável global declarada em processo.h
Processo* lista_de_processos;
extern unsigned char* memoria_fisica;
extern int num_total_quadros;

int criar_processo(int pid, int tamanho_processo) {
    // Validação 1: PID já existe?
    for (int i = 0; i < MAX_PROCESSOS; i++) {
        if (lista_de_processos[i]!= NULL && lista_de_processos[i]->pid == pid) {
            printf("Erro: PID %d já está em uso.\n", pid);
            return -1;
        }
    }

    // Validação 2: Tamanho do processo excede o máximo?
    if (tamanho_processo <= 0 |
| tamanho_processo > TAMANHO_MAX_PROCESSO) {
        printf("Erro: Tamanho do processo (%d bytes) é inválido ou excede o máximo permitido (%d bytes).\n", tamanho_processo, TAMANHO_MAX_PROCESSO);
        return -1;
    }

    int num_paginas = (tamanho_processo + TAMANHO_PAGINA - 1) / TAMANHO_PAGINA;
    
    // Validação 3: Há quadros livres suficientes?
    int quadros_livres_cont = 0;
    for(int i = 0; i < num_total_quadros; i++) {
        if(is_frame_free(i)) {
            quadros_livres_cont++;
        }
    }
    if (quadros_livres_cont < num_paginas) {
        printf("Erro: Memória física insuficiente para alocar %d páginas para o processo %d.\n", num_paginas, pid);
        return -1;
    }
    
    // Encontrar um slot livre na lista de processos
    int slot_processo = -1;
    for (int i = 0; i < MAX_PROCESSOS; i++) {
        if (lista_de_processos[i] == NULL) {
            slot_processo = i;
            break;
        }
    }
    if (slot_processo == -1) {
        printf("Erro: Limite máximo de processos (%d) atingido.\n", MAX_PROCESSOS);
        return -1;
    }

    // Alocação das estruturas do processo
    Processo* novo_processo = (Processo*) malloc(sizeof(Processo));
    if (novo_processo == NULL) {
        perror("Falha ao alocar a estrutura do processo");
        return -1;
    }
    novo_processo->tabela_paginas = (int*) malloc(num_paginas * sizeof(int));
    if (novo_processo->tabela_paginas == NULL) {
        perror("Falha ao alocar a tabela de páginas");
        free(novo_processo);
        return -1;
    }

    novo_processo->pid = pid;
    novo_processo->tamanho_logico = tamanho_processo;
    novo_processo->num_paginas = num_paginas;

    // Alocação de quadros e preenchimento da memória
    for (int i = 0; i < num_paginas; i++) {
        int quadro_livre = encontrar_quadro_livre();
        marcar_quadro_ocupado(quadro_livre);
        novo_processo->tabela_paginas[i] = quadro_livre;

        int base_addr = quadro_livre * TAMANHO_PAGINA;
        for (int j = 0; j < TAMANHO_PAGINA; j++) {
            if ((i * TAMANHO_PAGINA + j) < tamanho_processo) {
                memoria_fisica[base_addr + j] = rand() % 256;
            } else {
                memoria_fisica[base_addr + j] = 0x00; // Fragmentação interna
            }
        }
    }

    lista_de_processos[slot_processo] = novo_processo;
    printf("Processo %d criado com sucesso, ocupando %d páginas.\n", pid, num_paginas);
    return 0;
}

void visualizar_tabela_paginas(int pid) {
    Processo* p = NULL;
    for (int i = 0; i < MAX_PROCESSOS; i++) {
        if (lista_de_processos[i]!= NULL && lista_de_processos[i]->pid == pid) {
            p = lista_de_processos[i];
            break;
        }
    }

    if (p == NULL) {
        printf("Erro: Processo com PID %d não encontrado.\n", pid);
        return;
    }

    printf("\n--- Tabela de Páginas do Processo %d ---\n", pid);
    printf("Tamanho Lógico: %d bytes, Páginas: %d\n", p->tamanho_logico, p->num_paginas);
    printf("+---------------+---------------+\n");
    printf("| Página Lógica | Quadro Físico |\n");
    printf("+---------------+---------------+\n");
    for (int i = 0; i < p->num_paginas; i++) {
        printf("| %02d | %02d |\n", i, p->tabela_paginas[i]);
    }
    printf("+---------------+---------------+\n");
}