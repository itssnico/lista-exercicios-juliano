
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>

// Definição da estrutura para um nó na lista de adjacência
typedef struct NoListaAdjacente {
    int destino; // Vértice de destino da aresta
    struct NoListaAdjacente* proximo; // Ponteiro para o próximo nó na lista
} NoListaAdjacente;

// Definição da estrutura para uma lista de adjacência
typedef struct ListaAdjacente {
    NoListaAdjacente* cabeca; // Ponteiro para o primeiro nó na lista
} ListaAdjacente;

// Definição da estrutura para um grafo customizado
typedef struct GrafoCustomizado {
    int V; // Número de vértices
    ListaAdjacente* array; // Array de listas de adjacência
} GrafoCustomizado;

// Definição da estrutura para uma aresta customizada
typedef struct ArestaCustomizada {
    int verticeInicial; // Vértice de origem da aresta
    int verticeFinal; // Vértice de destino da aresta
} ArestaCustomizada;

// Função para criar um novo nó na lista de adjacência
NoListaAdjacente* criarNoListaAdjacente(int destino) {
    NoListaAdjacente* novoNo = (NoListaAdjacente*)malloc(sizeof(NoListaAdjacente)); // Aloca memória para o novo nó
    novoNo->destino = destino; // Define o destino do nó
    novoNo->proximo = NULL;
    return novoNo; // Retorna o novo nó criado
}

// Função para criar um grafo customizado com um número específico de vértices
GrafoCustomizado* criarGrafoCustomizado(int V) {
    int i;
    GrafoCustomizado* grafo = (GrafoCustomizado*)malloc(sizeof(GrafoCustomizado)); // Aloca memória para o grafo
    grafo->V = V; // Define o número de vértices do grafo
    grafo->array = (ListaAdjacente*)malloc((V + 1) * sizeof(ListaAdjacente)); // Aloca memória para o array de listas de adjacência
    for (i = 1; i <= V; ++i)
        grafo->array[i].cabeca = NULL;
    return grafo; // Retorna o grafo criado
}

// Função para adicionar uma aresta entre dois vértices no grafo customizado
void adicionarArestaCustomizada(GrafoCustomizado* grafo, int origem, int destino) {
    NoListaAdjacente* novoNo = criarNoListaAdjacente(destino); // Cria um novo nó para o destino na lista de adjacência da origem
    novoNo->proximo = grafo->array[origem].cabeca; // Aponta o próximo do novo nó para a cabeça da lista da origem
    grafo->array[origem].cabeca = novoNo; // Atualiza a cabeça da lista da origem para o novo nó

    novoNo = criarNoListaAdjacente(origem); // Cria um novo nó para a origem na lista de adjacência do destino
    novoNo->proximo = grafo->array[destino].cabeca; // Aponta o próximo do novo nó para a cabeça da lista do destino
    grafo->array[destino].cabeca = novoNo; // Atualiza a cabeça da lista do destino para o novo nó
}

// Função para buscar um caminho entre dois vértices no grafo customizado
void buscarCaminhoCustomizado(GrafoCustomizado* grafo, int origem, int destino) {
    int* visitados = (int*)calloc(grafo->V + 1, sizeof(int)); // Aloca memória para um vetor de visitados
    int* predecessores = (int*)malloc((grafo->V + 1) * sizeof(int)); // Aloca memória para um vetor de predecessores
    int* fila = (int*)malloc((grafo->V + 1) * sizeof(int)); // Aloca memória para uma fila
    int i;
    for (i = 1; i <= grafo->V; ++i)
        predecessores[i] = -1; // Inicializa os predecessores como -1

    int frente = 0, tras = 0; // Inicializa a frente e o fim da fila
    visitados[origem] = 1; // Marca o vértice de origem como visitado
    fila[tras++] = origem; // Adiciona o vértice de origem na fila
    while (frente != tras) { // Enquanto a fila não estiver vazia
        int u = fila[frente++]; // Remove o primeiro elemento da fila
        if (u == destino) // Se o vértice removido for o destino, encerra o loop
            break;
        NoListaAdjacente* j;
        for (j = grafo->array[u].cabeca; j != NULL; j = j->proximo) { // Percorre a lista de adjacência do vértice removido
            int v = j->destino; // Obtém o destino do nó
            if (!visitados[v]) { // Se o destino não foi visitado
                visitados[v] = 1; // Marca o destino como visitado
                predecessores[v] = u; // Define o vértice removido como predecessor do destino
                fila[tras++] = v; // Adiciona o destino na fila
            }
        }
    }
    if (predecessores[destino] != -1) { // Se existe um caminho até o destino
    	int atual;
        printf("Caminho de %d até %d: ", origem, destino); // Imprime a mensagem de caminho encontrado
        int* pilha = (int*)malloc((grafo->V + 1) * sizeof(int)); // Aloca memória para uma pilha
        int topo = -1; // Inicializa o topo da pilha como -1
        for (atual = destino; atual != -1; atual = predecessores[atual]) // Percorre os predecessores até o destino
            pilha[++topo] = atual; // Empilha os vértices no caminho
        while (topo != -1) { // Enquanto a pilha não estiver vazia
            printf("%d", pilha[topo--]); // Desempilha e imprime os vértices do caminho
            if (topo != -1) { // Se ainda houver elementos na pilha
                printf(" -> "); // Imprime uma seta entre os vértices
            }
        }
        printf("\n"); // Quebra de linha
        free(pilha); // Libera a memória alocada para a pilha
    } else {
        printf("Não foi possível encontrar um caminho entre %d e %d\n", origem, destino); // Imprime a mensagem de caminho não encontrado
    }
    free(visitados); // Libera a memória alocada para o vetor de visitados
    free(predecessores); // Libera a memória alocada para o vetor de predecessores
    free(fila); // Libera a memória alocada para a fila
}

int main(void) {
    setlocale(LC_ALL,"Portuguese"); // Define a localização para Português
    int numVertices, origem, destino, numArestas, i;
    char continuar;

    do {
        printf("Digite a quantidade de Vértices: ");
        scanf("%d", &numVertices); // Lê o número de vértices
        printf("\n");

        GrafoCustomizado* grafo = criarGrafoCustomizado(numVertices); // Cria um grafo com o número de vértices especificado

        printf("Digite a quantidade de Arestas: ");
        scanf("%d", &numArestas); // Lê o número de arestas
        printf("\n");

        for (i = 0; i < numArestas; ++i) { // Para cada aresta
            int origem, destino;
            printf("Digite a origem e o destino da aresta %d: ", i + 1);
            scanf("%d %d", &origem, &destino); // Lê a origem e o destino da aresta
            adicionarArestaCustomizada(grafo, origem, destino); // Adiciona a aresta ao grafo
            printf("\n");
        }

        printf("Digite o Vértice de Origem: ");
        scanf("%d", &origem); // Lê o vértice de origem
        printf("\n");
        printf("Digite o Vértice de Destino: ");
        scanf("%d", &destino); // Lê o vértice de destino
        printf("\n");

        buscarCaminhoCustomizado(grafo, origem, destino); // Busca um caminho entre os vértices de origem e destino

        printf("Deseja fazer mais um teste? (Digite 's' para fazer mais um teste e 'n' para sair): ");
        scanf(" %c", &continuar); // Pergunta ao usuário se deseja fazer outro teste
        printf("\n");

        free(grafo->array); // Libera a memória alocada para o array de listas de adjacência do grafo
        free(grafo); // Libera a memória alocada para o grafo

    } while (continuar != 'n'); // Repete o processo até o usuário optar por sair

    return 0;
}
