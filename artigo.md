# Comparando algoritmos de pesquisa: Uma análise empírica entre Pesquisa Sequencial e Pesquisa Binária

**Autores:** Marcelo Henrique / Leonardo Silva, Marcelo Eustáquio (Professor)
**Instituição:** Universidade Católica de Brasília – UCB
**Disciplina:** Análise de Algoritmos – 1° semestre de 2026

---

## 1. Resumo
Este artigo apresenta uma análise comparativa do desempenho e funcionamento dos algoritmos de pesquisa Sequencial e Binária aplicados a grandes conjuntos de dados. O estudo empírico foi realizado implementando os métodos na linguagem C e submetendo-os a vetores numéricos de 100.000, 200.000 e 300.000 elementos aleatórios. Os resultados validam as complexidades teóricas esperadas: a pesquisa sequencial demonstrou degradação de desempenho linear $O(N)$ fortemente influenciada pela posição da chave no vetor, enquanto a pesquisa binária sustentou tempos de resposta próximos e estáveis confirmando sua característica logarítmica $O(\log N)$, exigindo, no entanto, um custo inicial computacional para a ordenação prévia do vetor.

**Palavras-chave:** Algoritmos de Pesquisa, Pesquisa Sequencial, Pesquisa Binária, Complexidade de Algoritmos, Análise Empírica, Linguagem C.

---

## 2. Introdução
A busca por informações em estruturas de dados é uma operação central no desenvolvimento de sistemas. Escolher a estrutura e o algoritmo adequados pode definir a viabilidade de sistemas críticos, como bancos de dados, motores de buscas na internet e roteamento de redes.

No contexto de arranjos lineares (vetores), destacam-se dois métodos clássicos de pesquisa: a Pesquisa Sequencial e a Pesquisa Binária. A pesquisa sequencial baseia-se na verificação individual e exaustiva de cada elemento, possuindo como trunfo não requerer pré-requisitos em relação aos dados. Por outro lado, a pesquisa binária tira proveito da ordenação prévia do conjunto para aplicar uma estratégia de divisão e conquista, dividindo progressivamente o espaço de busca pela metade.

O objetivo deste trabalho prático é verificar e documentar as diferenças teóricas em um cenário experimental empírico real, quantificando o volume de comparações, cronometrando a execução física dos processadores na casa de frações de microssegundos e observando como a dimensão dos dados (100.000 a 300.000 elementos) e a localização do elemento buscado afetam o desempenho final dos dois métodos.

---

## 3. Fundamentação Teórica

### Pesquisa Sequencial
O método sequencial é a técnica iterativa direta. Consiste em comparar iterativamente o termo de busca (chave) com o primeiro elemento do conjunto, o segundo, o terceiro, até encontrar um valor correspondente (busca bem-sucedida) ou chegar ao último índice (busca malsucedida). O método possui complexidade de tempo de $O(N)$, implicando um crescimento linear e tempo proporcional ao número de registros. O número médio de comparações de sucesso em chaves randômicas em um vetor ordenado (ou não) é de $(N + 1)/2$. No pior caso, se a chave não estiver lá, exatamente $N$ comparações são executadas.

### Pesquisa Binária
Para usufruir desta pesquisa, requer-se obrigatoriamente um vetor previamente ordenado. A busca checa o elemento central; caso a chave almejada seja menor, descarta a metade superior inteira. Caso seja maior, descarta-se a metade inferior. Essa divisão contínua prossegue até a chave ser localizada ou o subconjunto alvo se esvaziar. Por dividir o problema progressivamente na base dois, a complexidade no pior caso de tempo é logarítmica $O(\log N)$. Isso significa que as comparações máximas realizadas escalam a passos infinitesimais mesmo em bilhões de registros.

### Custo de Ordenação
Como dito, a ordenação dos dados precede o uso de Pesquisas Binárias. Ordenar vetores via Quick Sort (o algoritmo adotado na implementação), provê tempo proporcional a $O(N \log N)$. Para consultas esparsas ou únicas, o custo de alinhar inteiramente o array ultrapassa substancialmente a verificação exaustiva.

---

## 4. Metodologia

Os algoritmos foram implementados inteiramente na linguagem C. 

Para a geração dos valores pseudoaleatórios e simulação de entropia real, utilizou-se a função nativa `rand()` da biblioteca `stdlib.h` atrelada à inicialização fixa com os últimos 3 dígitos da matrícula (`srand(123)` neste exemplo) para garantir o comportamento replicável. A ordenação dos vetores foi alcançada integrando a solução flexível da biblioteca nativa `qsort()` configurada para tipos interios ascendentes.

Os testes de pesquisa visavam calcular a repetição sistêmica. Devido aos ínfimos "clocks" executados por iteradores contemporâneos na pesquisa binária, cada medição isolada corria o risco de pontuar "0.0000". Para a obtenção dos milissegundos precisos apresentados nos dados experimentais, **cada posição de busca rodou internamente $R = 100.000$ vezes (cem mil repetições)**, para depois o tempo total ser extraído sobre essa base amostral e dividido por $R$, atingindo precisões relativas em nanossegundos ($10^{-9}$).

**Ambiente Computacional:**
*   **Sistema Operacional:** macOS
*   **Processador:** Apple Silicon (ARM64)
*   **Memória disponível:** Padrão do sistema
*   **Compilador:** `gcc` (Apple clang versão 15.x / LLVM), configurado com oclusão de otimização pesada (`-O0`) para não suprimir iteradores intencionalmente repetitivos.
*   **Semente (`srand`):** 123
*   **Algoritmo de ordenação:** `qsort` do C (implementação de Quicksort / Introsort híbrido).
*   **Quantidade de repetições ($R$):** 100.000
*   **Unidade de tempo:** Segundos (s), adaptado nos textos p/ Nanossegundos (ns) e Microssegundos ($\mu s$).

**Critério de Contagem de Comparações:**
Foi delimitado que cada avaliação posicional ou desigualitária conta. Na busca sequencial apenas o passo de equivalência (`if (V[i] == Chave)`) é realizado por ciclo (ou seja, 1 por ciclo). Já na Busca Binária, contabiliza-se duas verificações por ciclo: uma equivalência exata (`if (V[Meio] == Chave)`) e uma validação de corte direcional (`if (V[Meio] < Chave)`).

---

## 5. Resultados e Discussão

As simulações revelaram com precisão técnica a escalabilidade do algoritmo para os três dimensionamentos: 100 mil, 200 mil e 300 mil elementos.

### 5.1. Tempo de Geração de Vetores e Ordenação

O preenchimento do vetor aleatório apresentou tempo irrelevante no programa (0.0009s para 100k, 0.0030s para 300k).
A tabela a seguir pontua os custos envolvidos em ordenar o vetor.

| Tamanho (N) | T. Ord. Exp 1 (s) | T. Ord. Exp 2 (s) | T. Ord. Exp 3 (s) | T. Ord. Exp 4 (s) | Média Ord. (s) |
|-------------|-------------------|-------------------|-------------------|-------------------|----------------|
| **100.000** | 0.0120 | 0.0098 | 0.0088 | 0.0081 | **0.0097** |
| **200.000** | 0.0157 | 0.0147 | 0.0138 | 0.0137 | **0.0145** |
| **300.000** | 0.0217 | 0.0217 | 0.0217 | 0.0215 | **0.0216** |

Observou-se um crescimento moderado do tempo. O tempo médio de ordenação não dobrou entre 100k e 200k, nem triplicou para 300k, apresentando o padrão sub-quadrático $N \log N$ provido pelo `qsort`. 

Para um vetor futuro de 500.000, considerando a proporcionalidade observada, projeta-se um tempo médio variando em torno de **0.035 a 0.040 segundos**, uma vez que os limites teóricos e logarítmicos continuam suprimindo estornos exponenciais.

### 5.2. Análise de Comparações

O quadro documenta as medições do núcleo interno, expondo as chaves avaliadas nos marcos fixos.

| Tamanho | Chave (Posição) | Comparações Sequencial | Comparações Binária |
|---------|-----------------|------------------------|---------------------|
| 100.000 | Início | 1 | 31 |
| 100.000 | 25% | 25.001 | 31 |
| 100.000 | Centro | 50.001 | 31 |
| 100.000 | 75% | 75.001 | 31 |
| 100.000 | Final | 100.000 | 33 |
| 200.000 | Início | 1 | 33 |
| 200.000 | 25% | 50.001 | 33 |
| 200.000 | Centro | 100.001 | 33 |
| 200.000 | 75% | 150.001 | 33 |
| 200.000 | Final | 200.000 | 35 |
| 300.000 | Início | 1 | 35 |
| 300.000 | 25% | 75.001 | 35 |
| 300.000 | Centro | 150.001 | 35 |
| 300.000 | 75% | 225.001 | 35 |
| 300.000 | Final | 300.000 | 37 |

**Análise do pior caso e Limites Teóricos $\lceil\log_2 N\rceil$:**

| Tamanho de N | Limite Teórico ($\log_2 N$) | Comparações Binárias Totais Máximas (Vistas) |
|--------------|--------------------------|----------------------------------------------|
| **100.000** | 17 | 33 |
| **200.000** | 18 | 35 |
| **300.000** | 19 | 37 |
| **500.000** | 19 | -- |

A razão prática da pesquisa binária exceder a quantia pontual de 19 e cravar em até 37 reside na arquitetura sintática de blocos da condicional C: a cada laço while, aplicam-se duas validações no `if-else` em nosso controle interno (como detalhado na Metodologia). Ao calcular as quebras do laço (37 divido por 2), visualizamos quase perfeitamente as 18 a 19 divisões previstas na teoria (função logarítmica).

### 5.3. Tempo Médio das Pesquisas e Impacto Direto

| N | Posição | T. Médio Seq. (s) | T. Médio Bin. (s) |
|---|---------|-------------------|-------------------|
| 100.000 | Início | 0.000000002 | 0.000000030 |
| 100.000 | 25% | 0.000016578 | 0.000000030 |
| 100.000 | Centro | 0.000033568 | 0.000000030 |
| 100.000 | Final | 0.000067338 | 0.000000034 |
| 200.000 | Centro | 0.000067339 | 0.000000033 |
| 200.000 | Final | 0.000135474 | 0.000000037 |
| 300.000 | Centro | 0.000102567 | 0.000000036 |
| 300.000 | Final | 0.000204062 | 0.000000039 |

**Respostas Experimentais e Questionamentos Analíticos:**
1. **Qual algoritmo apresentou menor tempo médio?** A Pesquisa Binária se superou na esmagadora maioria, marcando taxas constantes de ~30 nanossegundos independentemente de ser 100 mil ou 300 mil elementos.
2. **Posição da chave e seu impacto:** Na busca Sequencial, um número no fim do conjunto de 300 mil demorou ~0.2 milissegundos. Ao mesmo tempo, se a chave localiza-se na primeira posição (Início), o mesmo método terminou em meros 0.000000002s, ou seja, dois nanossegundos - configurando o único pico isolado onde a lógica sequencial "grita e vence" o overhead binário inicial e encerra precocemente. A pesquisa binária atestou tempo unânime para todos.
3. **Pior Caso:** Buscar uma chave de preenchimento `(-1)` inexistente exigiu a validação total. Nesses eventos, o `for` linear de 300.000 voltas explodiu a contagem para N (trezentos mil acessos no array), mas o tempo binário permaneceu blindado.
4. **Crescimento Linear:** Dobrando N de 100k (0.067 ms para buscar no final) para 200k (0.135 ms para final), o tempo espelha o modelo empírico de um loop puro e contínuo, crescendo com linearidade explícita.
5. **Trade-off da Ordenação vs Pesquisas:** A ordenação do maior volume durou cerca de `21 ms`. Uma pesquisa no pior caso consome `0.2 ms`. Com base nesse peso experimental, valerá a pena ordenar o vetor inteiro *apenas se* estimarmos realizar pelo menos de $\sim 100$ consultas futuras variadas na aplicação, amortizando a margem gasta para alinhar o vetor inicial.

---

## 6. Conclusão
A experimentação corroborou incontestavelmente os modelos de complexidade algorítmica teórica. As diferenças pontuais no custo de execução demonstram que algoritmos com curva $O(N)$ são reativos demais à influência espacial do alvo: se o objeto está no começo, o programa é rápido, contudo os piores casos sufocam escalabilidade em massa de dados de um sistema de software real.

Observou-se as evidentes vantagens da complexidade subjacente da Pesquisa Binária $O(\log N)$. Apesar da exigência e overhead primário imposto por bibliotecas de classificação (como `qsort`), que devem ser balanceados na engenharia de sistemas antes da implementação, a resposta da divisão simétrica protegeu de maneira impecável o tempo de acesso frente a incrementos exponenciais das amostras numéricas. Portanto, em cenários de alta variância, consultas contínuas ou de bancos massivos, a Pesquisa Binária deve ser estritamente preferida na arquitetura de aplicações de alta resiliência.

---

## 7. Referências
*   CORMEN, T. H.; LEISERSON, C. E.; RIVEST, R. L.; STEIN, C. **Algoritmos: teoria e prática**. Rio de Janeiro: Elsevier, 2012.
*   ZIVIANI, N. **Projeto de algoritmos com implementações em C e C++**. São Paulo: Thomson Learning, 2004.
*   Documentação da API C Padrão: `<stdlib.h>` e `<time.h>`.

---

## Apêndice - Código Fonte Implementado

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DDD 123 // Semente base da matrícula
#define R 100000 // Repetições em looping para o tempo

long long comp_seq = 0;
long long comp_bin = 0;

int PesquisaSequencial(int *V, int N, int Chave) {
    comp_seq = 0;
    for (int i = 0; i < N; i++) {
        comp_seq++;
        if (V[i] == Chave) return i;
    }
    return -1; // ERRO: Elemento não encontrado
}

int PesquisaBinaria(int *V, int N, int Chave) {
    int Esquerda = 0;
    int Direita = N - 1;
    comp_bin = 0;
    while (Esquerda <= Direita) {
        int Meio = Esquerda + (Direita - Esquerda) / 2;
        
        comp_bin++; // Contagem da 1ª equivalencia
        if (V[Meio] == Chave) return Meio;
        
        comp_bin++; // Contagem da 2ª desigualdade
        if (V[Meio] < Chave) 
            Esquerda = Meio + 1;
        else 
            Direita = Meio - 1;
    }
    return -1; // ERRO: Elemento não encontrado
}

int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// ... Outras funções auxiliares de timing/main() omitidas para brevidade ...
```
