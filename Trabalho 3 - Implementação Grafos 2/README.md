# Trabalho Prático - Grafos 2

Este repositório contém a implementação do estudo de Grafos atualizada com novas funções. O programa permite executar diversas operações em um grafo, incluindo importação, edição, algoritmos de buscas e menor caminho, além da exportação em arquivo de texto.

## Funcionalidades Atualizadas

1. **Importar** um grafo de um arquivo de texto (agora com nomes).
2. **Criar** um grafo vazio a partir de um número de vértices informado pelo usuário.
3. **Exibir** as adjacências.
4. **Consultar** se um vértice é adjacente a outro.
5. **Inserir** uma nova aresta.
6. **Inserir** arestas em conjunto.
7. **Remover** arestas.
8. **Editar** a coordenada dos vértices.
9. **Consultar** o primeiro adjacente de um vértice.
10. **Consultar** o próximo adjacente de um vértice a partir de um adjacente informado.
11. **Consultar** a lista completa de adjacentes de um vértice.
12. **Exportar** o grafo para um arquivo de texto.
13. **Editar** o nome de um vértice.
14. **Executar** busca em profundidade (DFS).
15. **Executar** busca em largura (BFS).
16. **Gerar** a árvore geradora mínima usando o algoritmo de Prim.
17. **Determinar** o menor caminho utilizando o algoritmo de Dijkstra.



## Formato do Arquivo

O grafo será importado e exportado em um arquivo de texto com o seguinte formato:

1. **Linha 1**: Indica se o grafo é direcionado (`sim` ou `nao`).
2. **Linha 2**: Número de vértices.
3. **Próximas linhas**: Identificação, coordenadas `(x, y)` e nome de cada vértice.
4. **Linha seguinte**: Quantidade de arestas.
5. **Próximas linhas**: Origem, destino e peso de cada aresta.

#### Exemplo de entrada:

```text
direcionado=nao
10
0 1 1 Pedro Santos
1 50 20 Mons Agnes
2 10 30 Vladivostok
3 12 50 Mount Gundabad
4 15 70 Mons La Hire
5 20 90 Coruscant
6 25 11 Mons Wolf
7 30 12 Cafarnaun
8 35 15 Mons Vitruvius
9 40 20 Qorikancha
10
0 1 50
0 9 20
1 2 35
2 3 1
3 4 10
4 5 28
5 6 13
6 7 41
7 8 8
8 9 39
```

