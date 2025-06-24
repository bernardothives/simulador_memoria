#ifndef CONFIG_H
#define CONFIG_H

// --- Configurações do Simulador ---

// Tamanho total da memória física em bytes. Deve ser uma potência de dois.
// Exemplo: 64 KB = 64 * 1024.
#define TAMANHO_MEMORIA_FISICA (1024 * 64)

// Tamanho de cada página e, consequentemente, de cada quadro de memória em bytes.
// Deve ser uma potência de dois.
// Exemplo: 4 KB = 4096.
#define TAMANHO_PAGINA 4096

// Tamanho máximo que um processo pode ter em bytes.
// Exemplo: 16 KB = 16 * 1024.
#define TAMANHO_MAX_PROCESSO (1024 * 16)

// Número máximo de processos que o simulador pode gerenciar simultaneamente.
#define MAX_PROCESSOS 10

#endif // CONFIG_H