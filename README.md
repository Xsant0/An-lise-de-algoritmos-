# Análise de Algoritmos - Comparação Empírica de Pesquisas

Este repositório contém a implementação da **Atividade Avaliativa 1** da disciplina Análise de Algoritmos (Universidade Católica de Brasília). O trabalho realiza uma experimentação prática, avaliando quantitativamente a Busca Sequencial e a Busca Binária em vetores de 100 mil a 500 mil posições.

## Estrutura do Repositório
*   `main.c`: Implementação completa e comentada das pesquisas.
*   `plot.py`: Script Python usado para derivar os quatro gráficos do artigo.
*   `artigo.md` / `artigo.pdf`: Artigo científico documentando a análise empírica, resultados e discussões, com base na norma solicitada.
*   `resultados.csv` e `resultados.txt`: Base de dados dos tempos (milissegundos) e repetições das pesquisas cronometradas.
*   `grafico_*.png`: Gráficos gerados.

## Reprodução do Experimento

**Compilação em C:**
O programa foi projetado para executar centenas de milhares de vezes para não anular a granularidade da medição de tempo no clock do Sistema Operacional. Por isso, a compilação propositalmente neutraliza a otimização de loops exaustivos vazios usando a *flag* `-O0`.

```bash
gcc -O0 -Wall -o main main.c -lm
./main | tee resultados.txt
```

**Geração dos Gráficos em Python:**
O script consome o `resultados.csv` originado na saída.
```bash
python3 -m venv venv
source venv/bin/activate
pip install matplotlib numpy
python plot.py
```
