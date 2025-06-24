#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utils.h"

int obter_inteiro_valido() {
    char buffer;
    long valor;
    char* endptr;

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin)!= NULL) {
            // Remove o newline, se existir
            buffer[strcspn(buffer, "\n")] = 0;

            valor = strtol(buffer, &endptr, 10);

            // Verifica se a conversão foi bem-sucedida e se não há lixo no final
            if (endptr == buffer |
| *endptr!= '\0') {
                printf("Entrada inválida. Por favor, insira um número inteiro: ");
            } else if (valor > INT_MAX |
| valor < INT_MIN) {
                printf("Valor fora do intervalo permitido. Tente novamente: ");
            } else {
                return (int)valor; // Sucesso
            }
        }
    }
}