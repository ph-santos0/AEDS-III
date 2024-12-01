# Trabalho Prático - Grafos

Este repositório contém a implementação de um estudo de Grafos. O programa permite executar diversas operações em um grafo, incluindo importação, edição e exportação em arquivo de texto.

## Funcionalidades

1. **Importar** um grafo de um arquivo de texto.  
2. **Criar** um grafo vazio a partir de um número de vértices informado pelo usuário.  
3. **Exibir** as adjacências (matriz ou lista de adjacências).  
4. **Consultar** se um vértice é adjacente a outro.  
5. **Inserir** uma nova aresta.  
6. **Remover** arestas.  
7. **Editar** a coordenada dos vértices.  
8. **Exportar** o grafo para um arquivo de texto.  

## Formato do Arquivo

A importação e exportação do grafo utiliza o seguinte formato:

1. Uma linha indicando se o grafo é direcionado ou não.  
2. Uma linha com um número indicando a quantidade de vértices.  
3. Uma linha para cada vértice contendo sua identificação e sua coordenada (x, y), em uma escala de 0 a 100.  
4. Uma linha contendo a quantidade de arestas.  
5. Uma linha para cada aresta, indicando o vértice de origem, o vértice de destino e o peso.  
