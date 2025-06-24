#ifndef GERENCIADOR_MEMORIA_H
#define GERENCIADOR_MEMORIA_H

// Inicializa todas as estruturas de dados do simulador.
void inicializar_simulador();

// Exibe o estado atual da memória física e do bitmap de quadros.
void visualizar_memoria();

// Libera toda a memória alocada dinamicamente pelo simulador.
void liberar_recursos();

// Funções de manipulação do bitmap de quadros livres.
void marcar_quadro_ocupado(int frame_num);
void marcar_quadro_livre(int frame_num);
int is_frame_free(int frame_num);
int encontrar_quadro_livre();

#endif // GERENCIADOR_MEMORIA_H