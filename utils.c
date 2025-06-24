// Arquivo: utils.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utils.h"

int obter_inteiro_valido() {
    // CORREÇÃO: O buffer era um 'char' único, incapaz de armazenar uma string.
    // Alterado para um vetor de char para armazenar a entrada do usuário.
    char buffer[256];
    long valor;
    char* endptr;

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Remove o caractere de nova linha '\n', se existir
            buffer[strcspn(buffer, "\n")] = 0;

            valor = strtol(buffer, &endptr, 10);

            // Verifica se a conversão foi bem-sucedida e se não há lixo no final
            // CORREÇÃO: Usado o operador lógico '||' em vez do bit-a-bit '|'.
            if (endptr == buffer || *endptr != '\0') {
                printf("Entrada inválida. Por favor, insira um número inteiro: ");
            // CORREÇÃO: Usado o operador lógico '||' em vez do bit-a-bit '|'.
            } else if (valor > INT_MAX || valor < INT_MIN) {
                printf("Valor fora do intervalo permitido. Tente novamente: ");
            } else {
                return (int)valor; // Sucesso
            }
        } else {
            // Lidar com erro de leitura (ex: EOF)
            exit(1);
        }
    }
}