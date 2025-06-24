#include <stdio.h>
#include "config.h"
#include "gerenciador_memoria.h"
#include "processo.h"
#include "utils.h"

void exibir_menu() {
    printf("\n--- Simulador de Gerenciamento de Memória com Paginação ---\n");
    printf("1. Visualizar Memória\n");
    printf("2. Criar Processo\n");
    printf("3. Visualizar Tabela de Páginas de um Processo\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
}

void ui_criar_processo() {
    int pid, tamanho;
    printf("Digite o PID do novo processo: ");
    pid = obter_inteiro_valido();
    printf("Digite o tamanho do processo em bytes: ");
    tamanho = obter_inteiro_valido();
    criar_processo(pid, tamanho);
}

void ui_visualizar_tabela() {
    int pid;
    printf("Digite o PID do processo para visualizar a tabela de páginas: ");
    pid = obter_inteiro_valido();
    visualizar_tabela_paginas(pid);
}

int main() {
    inicializar_simulador();
    int escolha;

    do {
        exibir_menu();
        escolha = obter_inteiro_valido();

        switch (escolha) {
            case 1:
                visualizar_memoria();
                break;
            case 2:
                ui_criar_processo();
                break;
            case 3:
                ui_visualizar_tabela();
                break;
            case 4:
                printf("Encerrando o simulador...\n");
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
        }
    } while (escolha!= 4);

    liberar_recursos();
    return 0;
}