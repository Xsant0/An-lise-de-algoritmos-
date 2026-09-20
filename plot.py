import matplotlib.pyplot as plt
import numpy as np

# Data
N = np.array([100000, 200000, 300000])

# Time sorting
t_ord = np.array([0.0097, 0.0145, 0.0216])

# Average time per search (calculating mean over the 5 valid positions + 1 invalid, or just worst case)
# Let's plot the average time for the 6 cases
t_seq_100k = np.mean([0.000000002, 0.000016578, 0.000033568, 0.000050251, 0.000067338, 0.000067258])
t_seq_200k = np.mean([0.000000002, 0.000033639, 0.000067339, 0.000100924, 0.000135474, 0.000136815])
t_seq_300k = np.mean([0.000000002, 0.000051152, 0.000102567, 0.000154225, 0.000204062, 0.000207464])

t_bin_100k = np.mean([0.000000030, 0.000000030, 0.000000030, 0.000000030, 0.000000034, 0.000000033])
t_bin_200k = np.mean([0.000000034, 0.000000033, 0.000000033, 0.000000033, 0.000000037, 0.000000035])
t_bin_300k = np.mean([0.000000035, 0.000000036, 0.000000036, 0.000000035, 0.000000039, 0.000000038])

t_seq = np.array([t_seq_100k, t_seq_200k, t_seq_300k]) * 1000000 # Convert to microseconds for readability
t_bin = np.array([t_bin_100k, t_bin_200k, t_bin_300k]) * 1000000 # Convert to microseconds

# Comparisons (worst case)
comp_seq = np.array([100000, 200000, 300000])
comp_bin = np.array([33, 35, 37]) # max observed

plt.figure(figsize=(8,5))
plt.plot(N, t_ord, marker='o', color='green', linewidth=2)
plt.title('Tempo Médio de Ordenação vs Tamanho do Vetor')
plt.xlabel('Tamanho do Vetor (N)')
plt.ylabel('Tempo (segundos)')
plt.grid(True)
plt.xticks(N)
plt.savefig('/Users/marcelo/.gemini/antigravity/scratch/projeto_algoritmos/grafico_ordenacao.png')
plt.close()

plt.figure(figsize=(8,5))
plt.plot(N, t_seq, marker='o', label='Pesquisa Sequencial', linewidth=2)
plt.plot(N, t_bin, marker='s', label='Pesquisa Binária', linewidth=2)
plt.title('Tempo Médio de Pesquisa vs Tamanho do Vetor')
plt.xlabel('Tamanho do Vetor (N)')
plt.ylabel('Tempo Médio (microssegundos)')
plt.legend()
plt.grid(True)
plt.xticks(N)
plt.savefig('/Users/marcelo/.gemini/antigravity/scratch/projeto_algoritmos/grafico_tempo_pesquisa.png')
plt.close()

plt.figure(figsize=(8,5))
plt.plot(N, comp_seq, marker='o', label='Pesquisa Sequencial', linewidth=2)
plt.plot(N, comp_bin, marker='s', label='Pesquisa Binária', linewidth=2)
plt.title('Número Máximo de Comparações vs Tamanho do Vetor')
plt.xlabel('Tamanho do Vetor (N)')
plt.ylabel('Número de Comparações')
plt.yscale('log') # Log scale is better to show both
plt.legend()
plt.grid(True)
plt.xticks(N)
plt.savefig('/Users/marcelo/.gemini/antigravity/scratch/projeto_algoritmos/grafico_comparacoes.png')
plt.close()

print("Graficos gerados com sucesso.")
