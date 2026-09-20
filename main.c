#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DDD 123 // Semente ficticia (ultimos 3 digitos da matricula)
#define R 100000 // Repeticoes para as pesquisas

long long comp_seq = 0;
long long comp_bin = 0;

int PesquisaSequencial(int *V, int N, int Chave) {
    comp_seq = 0;
    for (int i = 0; i < N; i++) {
        comp_seq++;
        if (V[i] == Chave) return i;
    }
    return -1; // ERRO
}

int PesquisaBinaria(int *V, int N, int Chave) {
    int Esquerda = 0;
    int Direita = N - 1;
    comp_bin = 0;
    while (Esquerda <= Direita) {
        int Meio = Esquerda + (Direita - Esquerda) / 2;
        comp_bin++;
        if (V[Meio] == Chave) return Meio;
        
        comp_bin++;
        if (V[Meio] < Chave) 
            Esquerda = Meio + 1;
        else 
            Direita = Meio - 1;
    }
    return -1; // ERRO
}

int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void gerar_vetor(int N, double *tempos) {
    for (int i = 0; i < 4; i++) {
        clock_t inicio = clock();
        int *V = (int *) malloc(N * sizeof(int));
        if (V == NULL) {
            printf("ERRO: nao ha memoria para o vetor!\n");
            exit(1);
        }
        srand(DDD);
        for (int j = 0; j < N; j++) V[j] = rand();
        free(V);
        clock_t fim = clock();
        tempos[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }
}

void ordenar_vetor(int N, double *tempos) {
    for (int i = 0; i < 4; i++) {
        int *V = (int *) malloc(N * sizeof(int));
        srand(DDD);
        for (int j = 0; j < N; j++) V[j] = rand();
        
        clock_t inicio = clock();
        qsort(V, N, sizeof(int), cmpfunc);
        clock_t fim = clock();
        tempos[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        
        free(V);
    }
}

void avaliar_pesquisas(int N) {
    int *V = (int *) malloc(N * sizeof(int));
    srand(DDD);
    for (int j = 0; j < N; j++) V[j] = rand();
    qsort(V, N, sizeof(int), cmpfunc);

    // Definir as 6 chaves
    int chaves[6];
    chaves[0] = V[0];               // Inicio
    chaves[1] = V[N / 4];           // 25%
    chaves[2] = V[N / 2];           // Centro
    chaves[3] = V[(3 * N) / 4];     // 75%
    chaves[4] = V[N - 1];           // Final
    chaves[5] = -1;                 // Nao existe (sendo rand() positivo, -1 nao existe)

    const char* pos_nomes[] = {"Inicio", "25%", "Centro", "75%", "Final", "NaoExiste"};

    printf("\n--- Pesquisas para N = %d ---\n", N);
    printf("Posicao\tT_Seq(s)\tT_Bin(s)\tComp_Seq\tComp_Bin\tAchou_Seq\tAchou_Bin\n");
    
    for (int c = 0; c < 6; c++) {
        int chave = chaves[c];
        int achou_seq, achou_bin;

        // Sequencial
        clock_t inicio = clock();
        for (int r = 0; r < R; r++) {
            achou_seq = PesquisaSequencial(V, N, chave);
        }
        clock_t fim = clock();
        double tempo_seq = ((double)(fim - inicio)) / CLOCKS_PER_SEC / R;
        long long comps_seq = comp_seq; // Da ultima execucao

        // Binaria
        inicio = clock();
        for (int r = 0; r < R; r++) {
            achou_bin = PesquisaBinaria(V, N, chave);
        }
        fim = clock();
        double tempo_bin = ((double)(fim - inicio)) / CLOCKS_PER_SEC / R;
        long long comps_bin = comp_bin; // Da ultima execucao

        printf("%s\t%.9f\t%.9f\t%lld\t\t%lld\t\t%d\t\t%d\n", 
               pos_nomes[c], tempo_seq, tempo_bin, comps_seq, comps_bin, achou_seq, achou_bin);
    }
    free(V);
}

int main() {
    int tamanhos[] = {100000, 200000, 300000};
    double tempos_ger[4];
    double tempos_ord[4];

    printf("=== TEMPOS DE GERACAO DO VETOR ===\n");
    for (int i = 0; i < 3; i++) {
        gerar_vetor(tamanhos[i], tempos_ger);
        double soma = 0;
        printf("N=%d: ", tamanhos[i]);
        for(int t=0; t<4; t++) {
            printf("%.4f ", tempos_ger[t]);
            soma += tempos_ger[t];
        }
        printf("| Medio: %.4f\n", soma / 4.0);
    }

    printf("\n=== TEMPOS DE ORDENACAO ===\n");
    for (int i = 0; i < 3; i++) {
        ordenar_vetor(tamanhos[i], tempos_ord);
        double soma = 0;
        printf("N=%d: ", tamanhos[i]);
        for(int t=0; t<4; t++) {
            printf("%.4f ", tempos_ord[t]);
            soma += tempos_ord[t];
        }
        printf("| Medio: %.4f\n", soma / 4.0);
    }

    for (int i = 0; i < 3; i++) {
        avaliar_pesquisas(tamanhos[i]);
    }
    
    // Estimativa de 500.000 para ordenacao
    printf("\nLimite teorico log2(N):\n");
    printf("100.000: %.2f\n", ceil(log2(100000)));
    printf("200.000: %.2f\n", ceil(log2(200000)));
    printf("300.000: %.2f\n", ceil(log2(300000)));
    printf("500.000: %.2f\n", ceil(log2(500000)));

    return 0;
}
