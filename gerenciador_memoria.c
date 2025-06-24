// Arquivo: gerenciador_memoria.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config.h"
#include "gerenciador_memoria.h"
#include "processo.h"

// Variáveis globais que representam o estado da memória.
unsigned char* memoria_fisica;
unsigned char* bitmap_quadros_livres;
int num_total_quadros;

// Implementação das funções de manipulação de bits para o bitmap.
#define SET_BIT(bitmap, n) (bitmap[n/8] |= (1 << (n%8)))
#define CLEAR_BIT(bitmap, n) (bitmap[n/8] &= ~(1 << (n%8)))
#define TEST_BIT(bitmap, n) (bitmap[n/8] & (1 << (n%8)))

void inicializar_simulador() {
    memoria_fisica = (unsigned char*) malloc(TAMANHO_MEMORIA_FISICA);
    if (memoria_fisica == NULL) {
        perror("Falha ao alocar memória física");
        exit(EXIT_FAILURE);
    }
    memset(memoria_fisica, 0x00, TAMANHO_MEMORIA_FISICA);

    num_total_quadros = TAMANHO_MEMORIA_FISICA / TAMANHO_PAGINA;
    int bitmap_size = (num_total_quadros + 7) / 8;
    bitmap_quadros_livres = (unsigned char*) calloc(bitmap_size, sizeof(unsigned char));
    if (bitmap_quadros_livres == NULL) {
        perror("Falha ao alocar bitmap de quadros livres");
        free(memoria_fisica);
        exit(EXIT_FAILURE);
    }
    
    // CORREÇÃO: O loop abaixo para inicializar 'lista_de_processos' foi removido.
    // Como 'lista_de_processos' agora é um vetor global estático, o compilador
    // já garante que todos os seus elementos (ponteiros) sejam inicializados como NULL.
    // for (int i = 0; i < MAX_PROCESSOS; i++) {
    //     lista_de_processos[i] = NULL;
    // }

    srand(time(NULL));
    printf("Simulador inicializado com sucesso.\n");
    printf("Memória Física: %d bytes, Tamanho da Página: %d bytes, Total de Quadros: %d\n",
           TAMANHO_MEMORIA_FISICA, TAMANHO_PAGINA, num_total_quadros);
}

void marcar_quadro_ocupado(int frame_num) {
    // CORREÇÃO: Usado o operador lógico '||' em vez do bit-a-bit '|'.
    if (frame_num < 0 || frame_num >= num_total_quadros) return;
    SET_BIT(bitmap_quadros_livres, frame_num);
}

void marcar_quadro_livre(int frame_num) {
    // CORREÇÃO: Usado o operador lógico '||' em vez do bit-a-bit '|'.
    if (frame_num < 0 || frame_num >= num_total_quadros) return;
    CLEAR_BIT(bitmap_quadros_livres, frame_num);
}

int is_frame_free(int frame_num) {
    // CORREÇÃO: Usado o operador lógico '||' em vez do bit-a-bit '|'.
    if (frame_num < 0 || frame_num >= num_total_quadros) return 0;
    return !TEST_BIT(bitmap_quadros_livres, frame_num);
}

int encontrar_quadro_livre() {
    for (int i = 0; i < num_total_quadros; i++) {
        if (is_frame_free(i)) {
            return i;
        }
    }
    return -1; // Nenhum quadro livre encontrado
}

void visualizar_memoria() {
    int quadros_ocupados = 0;
    for (int i = 0; i < num_total_quadros; i++) {
        if (!is_frame_free(i)) {
            quadros_ocupados++;
        }
    }
    double percentual_ocupado = (num_total_quadros > 0) ? ((double)quadros_ocupados / num_total_quadros * 100.0) : 0.0;
    printf("\n--- Estado da Memória Física ---\n");
    printf("Ocupação: %d / %d quadros (%.2f%%)\n", quadros_ocupados, num_total_quadros, percentual_ocupado);
    printf("----------------------------------\n");

    for (int i = 0; i < num_total_quadros; i++) {
        printf("Quadro %03d: ", i);
        if (is_frame_free(i)) {
            printf("[ Livre ]\n");
        } else {
            int pid_dono = -1;
            int pagina_dona = -1;
            // Busca reversa para encontrar o dono do quadro
            for (int j = 0; j < MAX_PROCESSOS; j++) {
                if (lista_de_processos[j] != NULL) {
                    for (int k = 0; k < lista_de_processos[j]->num_paginas; k++) {
                        if (lista_de_processos[j]->tabela_paginas[k] == i) {
                            pid_dono = lista_de_processos[j]->pid;
                            pagina_dona = k;
                            goto found;
                        }
                    }
                }
            }
            found:
            printf("[ Ocupado por P%d, Página %d ] Conteúdo: ", pid_dono, pagina_dona);
            
            // CORREÇÃO: O printf estava imprimindo o endereço de 'memoria_fisica'
            // em vez do seu conteúdo. O correto é calcular o endereço base do quadro
            // e imprimir os bytes a partir dali.
            int base_addr = i * TAMANHO_PAGINA;
            for(int k = 0; k < 8 && k < TAMANHO_PAGINA; k++) {
                printf("%02X ", memoria_fisica[base_addr + k]);
            }
            printf("...\n");
        }
    }
    printf("----------------------------------\n");
}

void liberar_recursos() {
    free(memoria_fisica);
    free(bitmap_quadros_livres);
    for (int i = 0; i < MAX_PROCESSOS; i++) {
        if (lista_de_processos[i] != NULL) {
            free(lista_de_processos[i]->tabela_paginas);
            free(lista_de_processos[i]);
        }
    }
    // CORREÇÃO: Não é necessário liberar 'lista_de_processos' pois foi
    // alocado estaticamente como um vetor global.
    printf("Recursos do simulador liberados.\n");
}