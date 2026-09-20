#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DDD 123 // SEMENTE - Substituir pelos 3 ultimos digitos da matricula
#define R 100000 // Repeticoes

long long comp_seq = 0;
long long comp_bin = 0;

int PesquisaSequencial(int *V, int N, int Chave) {
    comp_seq = 0;
    for (int i = 0; i < N; i++) {
        comp_seq++;
        if (V[i] == Chave) return i;
    }
    return -1;
}

int PesquisaBinaria(int *V, int N, int Chave) {
    int Esquerda = 0;
    int Direita = N - 1;
    comp_bin = 0;
    while (Esquerda <= Direita) {
        int Meio = Esquerda + (Direita - Esquerda) / 2;
        comp_bin++;
        if (V[Meio] == Chave) return Meio;
        if (V[Meio] < Chave) 
            Esquerda = Meio + 1;
        else 
            Direita = Meio - 1;
    }
    return -1;
}

int cmpfunc(const void *a, const void *b) {
    long long diff = (long long)(*(int*)a) - (long long)(*(int*)b);
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

void verificar_ordenacao(int *V, int N) {
    for (int i = 0; i < N - 1; i++) {
        if (V[i] > V[i+1]) {
            printf("  [!] ERRO: Vetor nao ordenado na posicao %d\n", i);
            return;
        }
    }
    printf("  [+] ORDENACAO: OK\n");
}

void medir_geracao(int N, FILE *csv) {
    double tempos[4];
    double soma = 0;
    for (int i = 0; i < 4; i++) {
        clock_t inicio = clock();
        int *V = (int *) malloc(N * sizeof(int));
        if (!V) { printf("Erro alocacao\n"); exit(1); }
        srand(DDD);
        for (int j = 0; j < N; j++) V[j] = rand();
        free(V);
        clock_t fim = clock();
        tempos[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        soma += tempos[i];
    }
    double media = soma / 4.0;
    printf("Geracao N=%d: %.4fs %.4fs %.4fs %.4fs | Media: %.4fs\n", N, tempos[0], tempos[1], tempos[2], tempos[3], media);
    fprintf(csv, "geracao,%d,%.6f,%.6f,%.6f,%.6f,%.6f\n", N, tempos[0], tempos[1], tempos[2], tempos[3], media);
}

void medir_ordenacao(int N, FILE *csv) {
    double tempos[4];
    double soma = 0;
    for (int i = 0; i < 4; i++) {
        int *V = (int *) malloc(N * sizeof(int));
        if (!V) { printf("Erro alocacao\n"); exit(1); }
        srand(DDD);
        for (int j = 0; j < N; j++) V[j] = rand();
        
        clock_t inicio = clock();
        qsort(V, N, sizeof(int), cmpfunc);
        clock_t fim = clock();
        tempos[i] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        soma += tempos[i];
        
        if (i == 0) verificar_ordenacao(V, N); // Verifica no 1o exp
        free(V);
    }
    double media = soma / 4.0;
    printf("Ordenacao N=%d: %.4fs %.4fs %.4fs %.4fs | Media: %.4fs\n", N, tempos[0], tempos[1], tempos[2], tempos[3], media);
    fprintf(csv, "ordenacao,%d,%.6f,%.6f,%.6f,%.6f,%.6f\n", N, tempos[0], tempos[1], tempos[2], tempos[3], media);
}

void medir_pesquisas(int N, FILE *csv) {
    int *V = (int *) malloc(N * sizeof(int));
    srand(DDD);
    for (int j = 0; j < N; j++) V[j] = rand();
    qsort(V, N, sizeof(int), cmpfunc);

    int chaves[6];
    chaves[0] = V[0];               
    chaves[1] = V[N / 4];           
    chaves[2] = V[N / 2];           
    chaves[3] = V[(3 * N) / 4];     
    chaves[4] = V[N - 1];           
    chaves[5] = -1;                 

    const char* pos_nomes[] = {"Inicio", "25%", "Centro", "75%", "Final", "NaoExiste"};

    printf("\n--- Pesquisas para N = %d ---\n", N);
    
    for (int c = 0; c < 6; c++) {
        int chave = chaves[c];
        int achou_seq, achou_bin;

        // Sequencial
        clock_t inicio = clock();
        for (int r = 0; r < R; r++) achou_seq = PesquisaSequencial(V, N, chave);
        clock_t fim = clock();
        double tempo_seq = ((double)(fim - inicio)) / CLOCKS_PER_SEC / R;
        long long comps_seq = comp_seq;

        // Binaria
        inicio = clock();
        for (int r = 0; r < R; r++) achou_bin = PesquisaBinaria(V, N, chave);
        fim = clock();
        double tempo_bin = ((double)(fim - inicio)) / CLOCKS_PER_SEC / R;
        long long comps_bin = comp_bin;

        printf("Pos: %s\tChave: %d\tT_Seq: %.9fs\tT_Bin: %.9fs\tC_Seq: %lld\tC_Bin: %lld\tIdx_Seq: %d\tIdx_Bin: %d\n", 
               pos_nomes[c], chave, tempo_seq, tempo_bin, comps_seq, comps_bin, achou_seq, achou_bin);
               
        fprintf(csv, "pesquisa,%d,%s,%d,%.9f,%.9f,%lld,%lld,%d,%d\n", 
                N, pos_nomes[c], chave, tempo_seq, tempo_bin, comps_seq, comps_bin, achou_seq, achou_bin);
    }
    free(V);
}

int main() {
    printf("RAND_MAX do sistema: %d\n\n", RAND_MAX);
    FILE *csv = fopen("resultados.csv", "w");
    if (!csv) return 1;
    fprintf(csv, "tipo,tamanho,val1,val2,val3,val4,val5,val6,val7,val8\n"); // Header genérico

    int tamanhos[] = {100000, 200000, 300000, 500000};
    
    printf("=== TEMPOS DE GERACAO E ORDENACAO ===\n");
    for (int i = 0; i < 4; i++) {
        medir_geracao(tamanhos[i], csv);
        medir_ordenacao(tamanhos[i], csv);
    }

    for (int i = 0; i < 4; i++) {
        medir_pesquisas(tamanhos[i], csv);
    }

    fclose(csv);
    return 0;
}
