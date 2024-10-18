#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_EXECUCOES 20 // Número de execuções para medir o tempo

/**
 * Função para trocar os valores de duas variáveis inteiras.
 *
 * @param a Ponteiro para o primeiro inteiro.
 * @param b Ponteiro para o segundo inteiro.
 */
void troca(int *a, int *b) {
    const int t = *a;
    *a = *b;
    *b = t;
}

/**
 * Função para encontrar a mediana de três elementos em um array.
 *
 * @param A Array de inteiros.
 * @param low Índice inicial.
 * @param high Índice final.
 * @return A mediana dos três elementos.
 */
int medianaDeTres(int A[], const int low, const int high) {
    const int mid = low + (high - low) / 2;

    if (A[low] > A[mid]) troca(&A[low], &A[mid]);
    if (A[low] > A[high]) troca(&A[low], &A[high]);
    if (A[mid] > A[high]) troca(&A[mid], &A[high]);
    troca(&A[mid], &A[high - 1]);

    return A[high - 1];
}

/**
 * Função para particionar o array usando a mediana de três como pivô.
 *
 * @param A Array de inteiros.
 * @param low Índice inicial.
 * @param high Índice final.
 * @return O índice do pivô.
 */
int particiona(int A[], const int low, const int high) {
    const int pivot = medianaDeTres(A, low, high);
    int i = low;
    int j = high - 1;

    while (1) {
        while (A[++i] < pivot) {
        }
        while (A[--j] > pivot) {
        }
        if (i >= j) break;
        troca(&A[i], &A[j]);
    }
    troca(&A[i], &A[high - 1]);
    return i;
}

/**
 * Função para ordenar um array usando o algoritmo QuickSort.
 *
 * @param A Array de inteiros.
 * @param low Índice inicial.
 * @param high Índice final.
 */
void quickSort(int A[], int low, int high) {
    while (low < high) {
        const int pi = particiona(A, low, high);

        if (pi - low < high - pi) {
            quickSort(A, low, pi - 1);
            low = pi + 1;
        } else {
            quickSort(A, pi + 1, high);
            high = pi - 1;
        }
    }
}

/**
 * Função para ordenar um array usando o algoritmo Counting Sort.
 *
 * @param inputArray Array de inteiros a ser ordenado.
 * @param N Tamanho do array.
 */
void countingSort(int inputArray[], const int N) {
    // Encontrando o maior valor do array
    int M = 0;
    for (int i = 0; i < N; i++)
        if (inputArray[i] > M)
            M = inputArray[i];

    // Inicializando array countArray[] com zeros
    int *countArray = calloc(M + 1, sizeof(int));

    // Contando a ocorrência de cada elemento
    for (int i = 0; i < N; i++)
        countArray[inputArray[i]]++;

    // Acumulando as contagens
    for (int i = 1; i <= M; i++)
        countArray[i] += countArray[i - 1];

    // Criando o array de saída
    int *outputArray = malloc(N * sizeof(int));
    for (int i = N - 1; i >= 0; i--) {
        outputArray[countArray[inputArray[i]] - 1] = inputArray[i];
        countArray[inputArray[i]]--;
    }

    // Copiando outputArray[] para inputArray[]
    for (int i = 0; i < N; i++)
        inputArray[i] = outputArray[i];

    // Libera memória alocada
    free(countArray);
    free(outputArray);
}

/**
 * Função para medir o tempo de execução de uma função de ordenação.
 *
 * @param func Ponteiro para a função de ordenação.
 * @param A Array de inteiros a ser ordenado.
 * @param n Tamanho do array.
 * @return O tempo de execução em segundos.
 */
double medirTempo(void (*func)(int [], int, int), int A[], const int n) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    func(A, 0, n - 1);
    clock_gettime(CLOCK_MONOTONIC, &end);

    const double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed;
}

/**
 * Função para gerar uma lista aleatória de inteiros.
 *
 * @param A Array de inteiros.
 * @param n Tamanho do array.
 */
void gerarListaAleatoria(int A[], const int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % n;
    }
}

/**
 * Função para gerar uma lista crescente de inteiros.
 *
 * @param A Array de inteiros.
 * @param n Tamanho do array.
 */
void gerarListaCrescente(int A[], const int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

/**
 * Função para gerar uma lista decrescente de inteiros.
 *
 * @param A Array de inteiros.
 * @param n Tamanho do array.
 */
void gerarListaDecrescente(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

/**
 * Função para gerar uma lista de inteiros com base no tipo de ordenação.
 *
 * @param A Array de inteiros.
 * @param n Tamanho do array.
 * @param orderType Tipo de ordenação (0 para aleatória, 1 para crescente, 2 para decrescente).
 */
void gerarLista(int A[], const int n, const int orderType) {
    switch (orderType) {
        case 0:
            gerarListaAleatoria(A, n);
            break;
        case 1:
            gerarListaCrescente(A, n);
            break;
        case 2:
            gerarListaDecrescente(A, n);
            break;
        default:
            fprintf(stderr, "Erro: Tipo de lista inválido\n");
            exit(EXIT_FAILURE);
    }
}

/**
 * Função solicitada no trabalho para imprimir os dados
 *
 * @param A Array de inteiros.
 * @param n Tamanho do array.
 */
void printArray(int A[], const int n) {
    printf("\n[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", A[i], (i < n - 1) ? ", " : "");
    }
    printf("]\n");
}

/**
 * Função para calcular o desvio padrão de um array de tempos.
 *
 * @param tempos Array de tempos.
 * @param numExecucoes Número de execuções.
 * @param media Média dos tempos.
 * @return O desvio padrão dos tempos.
 */
double calcularDesvioPadrao(double tempos[], const int numExecucoes, const double media) {
    double soma = 0.0;
    for (int i = 0; i < numExecucoes; i++) {
        soma += pow(tempos[i] - media, 2);
    }
    return sqrt(soma / numExecucoes);
}

/**
 * Função para executar testes de ordenação.
 *
 * @param A Array de inteiros.
 * @param n Tamanho do array.
 * @param typeList Tipo de lista (0 para aleatória, 1 para crescente, 2 para decrescente).
 * @param sortFunc Ponteiro para a função de ordenação.
 * @param algoritmoStr Nome do algoritmo de ordenação.
 */
void executarTestes(int A[], const int n, const int typeList, void (*sortFunc)(int [], int, int), const char *algoritmoStr) {
    double tempos[NUM_EXECUCOES];
    double tempoExecucaoTotal = 0.0;

    for (int i = 0; i < NUM_EXECUCOES; i++) {
        gerarLista(A, n, typeList);
        // printArray(A, n); // Exibe a massa de dados gerada como solicitado no artigo. SÓ DESCOMENTAR PARA TESTE. No entanto, a execução será maior e vai exibir massa de dados gigantescas no terminal.
        tempos[i] = medirTempo(sortFunc, A, n);
        tempoExecucaoTotal += tempos[i];
    }

    const double tempoMedioExecucao = tempoExecucaoTotal / NUM_EXECUCOES;
    const double desvioPadrao = calcularDesvioPadrao(tempos, NUM_EXECUCOES, tempoMedioExecucao);

    const char *tipoListaStr = (typeList == 0) ? "Aleatoria" : (typeList == 1) ? "Crescente" : "Decrescente";

    printf("| %-13s | %-11d | %-13s | %-31f segundos | %-30f segundos | %-30f segundos |\n", algoritmoStr, n,
           tipoListaStr, tempoMedioExecucao, tempoExecucaoTotal, desvioPadrao);
}

/**
 * Função principal.
 *
 * \return 0, Indicando que o programa terminou sem erros.
 * \return 1, Indicando que o programa terminou com erros.
 * \return 139, Indicando que o programa foi interrompido por causa de um erro de segmentação (segmentation fault).
 */
int main() {
    const int tamanhos[] = {1000, 100000, 1000000};
    const int tiposLista[] = {0, 1, 2}; // 0: Aleatória, 1: Crescente, 2: Decrescente
    const char *algoritmos[] = {"Counting Sort", "QuickSort"};
    void (*funcoesOrdenacao[])(int [], int, int) = {countingSort, quickSort};
    // Esta linha serve para associar o nome do algoritmo com a função correspondente

    for (int alg = 0; alg < 2; alg++) {
        printf("%s\n", algoritmos[alg]);
        printf(
            "| Algoritmo     | N Elementos | Tipo de Lista | Média de Tempo (20 execuções)            | Tempo de finalização do processo        | Desvio padrão                           |\n");
        printf(
            "|---------------|-------------|---------------|------------------------------------------|-----------------------------------------|-----------------------------------------|\n");

        for (int s = 0; s < 3; s++) {
            const int n = tamanhos[s];

            for (int t = 0; t < 3; t++) {
                int *A = malloc(n * sizeof(int));

                if (A == NULL) {
                    fprintf(stderr, "Erro ao alocar memória para o array A\n");
                    exit(EXIT_FAILURE);
                }

                executarTestes(A, n, tiposLista[t], funcoesOrdenacao[alg], algoritmos[alg]);
                free(A);
            }
        }
        printf("\n");
    }
    return 0;
}
