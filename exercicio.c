
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>

// Defini��o da estrutura para um n� na lista de adjac�ncia
typedef struct NoListaAdjacente {
    int destino; // V�rtice de destino da aresta
    struct NoListaAdjacente* proximo; // Ponteiro para o pr�ximo n� na lista
} NoListaAdjacente;

// Defini��o da estrutura para uma lista de adjac�ncia
typedef struct ListaAdjacente {
    NoListaAdjacente* cabeca; // Ponteiro para o primeiro n� na lista
} ListaAdjacente;

// Defini��o da estrutura para um grafo customizado
typedef struct GrafoCustomizado {
    int V; // N�mero de v�rtices
    ListaAdjacente* array; // Array de listas de adjac�ncia
} GrafoCustomizado;

// Defini��o da estrutura para uma aresta customizada
typedef struct ArestaCustomizada {
    int verticeInicial; // V�rtice de origem da aresta
    int verticeFinal; // V�rtice de destino da aresta
} ArestaCustomizada;

// Fun��o para criar um novo n� na lista de adjac�ncia
NoListaAdjacente* criarNoListaAdjacente(int destino) {
    NoListaAdjacente* novoNo = (NoListaAdjacente*)malloc(sizeof(NoListaAdjacente)); // Aloca mem�ria para o novo n�
    novoNo->destino = destino; // Define o destino do n�
    novoNo->proximo = NULL;
    return novoNo; // Retorna o novo n� criado
}

// Fun��o para criar um grafo customizado com um n�mero espec�fico de v�rtices
GrafoCustomizado* criarGrafoCustomizado(int V) {
    int i;
    GrafoCustomizado* grafo = (GrafoCustomizado*)malloc(sizeof(GrafoCustomizado)); // Aloca mem�ria para o grafo
    grafo->V = V; // Define o n�mero de v�rtices do grafo
    grafo->array = (ListaAdjacente*)malloc((V + 1) * sizeof(ListaAdjacente)); // Aloca mem�ria para o array de listas de adjac�ncia
    for (i = 1; i <= V; ++i)
        grafo->array[i].cabeca = NULL;
    return grafo; // Retorna o grafo criado
}

// Fun��o para adicionar uma aresta entre dois v�rtices no grafo customizado
void adicionarArestaCustomizada(GrafoCustomizado* grafo, int origem, int destino) {
    NoListaAdjacente* novoNo = criarNoListaAdjacente(destino); // Cria um novo n� para o destino na lista de adjac�ncia da origem
    novoNo->proximo = grafo->array[origem].cabeca; // Aponta o pr�ximo do novo n� para a cabe�a da lista da origem
    grafo->array[origem].cabeca = novoNo; // Atualiza a cabe�a da lista da origem para o novo n�

    novoNo = criarNoListaAdjacente(origem); // Cria um novo n� para a origem na lista de adjac�ncia do destino
    novoNo->proximo = grafo->array[destino].cabeca; // Aponta o pr�ximo do novo n� para a cabe�a da lista do destino
    grafo->array[destino].cabeca = novoNo; // Atualiza a cabe�a da lista do destino para o novo n�
}

// Fun��o para buscar um caminho entre dois v�rtices no grafo customizado
void buscarCaminhoCustomizado(GrafoCustomizado* grafo, int origem, int destino) {
    int* visitados = (int*)calloc(grafo->V + 1, sizeof(int)); // Aloca mem�ria para um vetor de visitados
    int* predecessores = (int*)malloc((grafo->V + 1) * sizeof(int)); // Aloca mem�ria para um vetor de predecessores
    int* fila = (int*)malloc((grafo->V + 1) * sizeof(int)); // Aloca mem�ria para uma fila
    int i;
    for (i = 1; i <= grafo->V; ++i)
        predecessores[i] = -1; // Inicializa os predecessores como -1

    int frente = 0, tras = 0; // Inicializa a frente e o fim da fila
    visitados[origem] = 1; // Marca o v�rtice de origem como visitado
    fila[tras++] = origem; // Adiciona o v�rtice de origem na fila
    while (frente != tras) { // Enquanto a fila n�o estiver vazia
        int u = fila[frente++]; // Remove o primeiro elemento da fila
        if (u == destino) // Se o v�rtice removido for o destino, encerra o loop
            break;
        NoListaAdjacente* j;
        for (j = grafo->array[u].cabeca; j != NULL; j = j->proximo) { // Percorre a lista de adjac�ncia do v�rtice removido
            int v = j->destino; // Obt�m o destino do n�
            if (!visitados[v]) { // Se o destino n�o foi visitado
                visitados[v] = 1; // Marca o destino como visitado
                predecessores[v] = u; // Define o v�rtice removido como predecessor do destino
                fila[tras++] = v; // Adiciona o destino na fila
            }
        }
    }
    if (predecessores[destino] != -1) { // Se existe um caminho at� o destino
    	int atual;
        printf("Caminho de %d at� %d: ", origem, destino); // Imprime a mensagem de caminho encontrado
        int* pilha = (int*)malloc((grafo->V + 1) * sizeof(int)); // Aloca mem�ria para uma pilha
        int topo = -1; // Inicializa o topo da pilha como -1
        for (atual = destino; atual != -1; atual = predecessores[atual]) // Percorre os predecessores at� o destino
            pilha[++topo] = atual; // Empilha os v�rtices no caminho
        while (topo != -1) { // Enquanto a pilha n�o estiver vazia
            printf("%d", pilha[topo--]); // Desempilha e imprime os v�rtices do caminho
            if (topo != -1) { // Se ainda houver elementos na pilha
                printf(" -> "); // Imprime uma seta entre os v�rtices
            }
        }
        printf("\n"); // Quebra de linha
        free(pilha); // Libera a mem�ria alocada para a pilha
    } else {
        printf("N�o foi poss�vel encontrar um caminho entre %d e %d\n", origem, destino); // Imprime a mensagem de caminho n�o encontrado
    }
    free(visitados); // Libera a mem�ria alocada para o vetor de visitados
    free(predecessores); // Libera a mem�ria alocada para o vetor de predecessores
    free(fila); // Libera a mem�ria alocada para a fila
}

int main(void) {
    setlocale(LC_ALL,"Portuguese"); // Define a localiza��o para Portugu�s
    int numVertices, origem, destino, numArestas, i;
    char continuar;

    do {
        printf("Digite a quantidade de V�rtices: ");
        scanf("%d", &numVertices); // L� o n�mero de v�rtices
        printf("\n");

        GrafoCustomizado* grafo = criarGrafoCustomizado(numVertices); // Cria um grafo com o n�mero de v�rtices especificado

        printf("Digite a quantidade de Arestas: ");
        scanf("%d", &numArestas); // L� o n�mero de arestas
        printf("\n");

        for (i = 0; i < numArestas; ++i) { // Para cada aresta
            int origem, destino;
            printf("Digite a origem e o destino da aresta %d: ", i + 1);
            scanf("%d %d", &origem, &destino); // L� a origem e o destino da aresta
            adicionarArestaCustomizada(grafo, origem, destino); // Adiciona a aresta ao grafo
            printf("\n");
        }

        printf("Digite o V�rtice de Origem: ");
        scanf("%d", &origem); // L� o v�rtice de origem
        printf("\n");
        printf("Digite o V�rtice de Destino: ");
        scanf("%d", &destino); // L� o v�rtice de destino
        printf("\n");

        buscarCaminhoCustomizado(grafo, origem, destino); // Busca um caminho entre os v�rtices de origem e destino

        printf("Deseja fazer mais um teste? (Digite 's' para fazer mais um teste e 'n' para sair): ");
        scanf(" %c", &continuar); // Pergunta ao usu�rio se deseja fazer outro teste
        printf("\n");

        free(grafo->array); // Libera a mem�ria alocada para o array de listas de adjac�ncia do grafo
        free(grafo); // Libera a mem�ria alocada para o grafo

    } while (continuar != 'n'); // Repete o processo at� o usu�rio optar por sair

    return 0;
}
