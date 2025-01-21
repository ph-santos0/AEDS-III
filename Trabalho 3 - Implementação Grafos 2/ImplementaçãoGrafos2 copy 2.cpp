#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

struct Coordenada
{
    int x;
    int y;
};

struct Aresta
{
    int vertice;
    int peso;
};

bool direcionado;
int numVertices;
vector<Coordenada> coordenadas;
vector<vector<Aresta>> adjacencias;
vector<string> nomesVertices;

void limparGrafo()
{
    coordenadas.clear();
    adjacencias.clear();
    nomesVertices.clear();
}

void exibirAdjacencias()
{
    cout << "===== Adjacências =====\n";
    for (int i = 0; i < numVertices; i++)
    {
        cout << "Vértice " << i << " (" << nomesVertices[i] << "):";
        if (!adjacencias[i].empty())
        {
            for (int j = 0; j < adjacencias[i].size(); j++)
            {
                cout << " -> " << adjacencias[i][j].vertice;
            }
        }
        else
        {
            cout << " sem adjacências";
        }
        cout << endl;
    }
    cout << "========================\n";
}

void inserirAresta(int v1, int v2, int peso)
{
    adjacencias[v1].push_back({v2, peso});
    if (!direcionado)
    {
        adjacencias[v2].push_back({v1, peso});
    }
}

void importarGrafo(const char *arquivo)
{
    ifstream file(arquivo);
    if (!file.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    string linha;
    getline(file, linha);
    direcionado = (linha.find("sim") != string::npos);

    file >> numVertices;
    coordenadas.resize(numVertices);
    adjacencias.resize(numVertices);
    nomesVertices.resize(numVertices);

    for (int i = 0; i < numVertices; i++)
    {
        int id, x, y;
        string nome;
        file >> id >> x >> y;
        getline(file, nome);
        if (!nome.empty() && nome[0] == ' ')
            nome.erase(0, 1);
        coordenadas[id] = {x, y};
        nomesVertices[id] = nome;
    }

    int numArestas;
    file >> numArestas;

    for (int i = 0; i < numArestas; i++)
    {
        int v1, v2, peso;
        file >> v1 >> v2 >> peso;
        inserirAresta(v1, v2, peso);
    }

    file.close();
    cout << "Grafo importado com sucesso!\n";
}

void kruskal()
{
    vector<pair<int, pair<int, int>>> arestas;
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < adjacencias[i].size(); j++)
        {
            int v1 = i;
            int v2 = adjacencias[i][j].vertice;
            int peso = adjacencias[i][j].peso;

            if (v1 < v2)
            {
                arestas.push_back({peso, {v1, v2}});
            }
        }
    }

    for (int i = 0; i < arestas.size(); i++)
    {
        for (int j = i + 1; j < arestas.size(); j++)
        {
            if (arestas[i].first > arestas[j].first)
            {
                swap(arestas[i], arestas[j]);
            }
        }
    }

    vector<int> pai(numVertices);
    for (int i = 0; i < numVertices; i++)
    {
        pai[i] = i;
    }

    auto encontrar = [&](int v)
    {
        while (v != pai[v])
        {
            v = pai[v];
        }
        return v;
    };

    auto unir = [&](int v1, int v2)
    {
        int raiz1 = encontrar(v1);
        int raiz2 = encontrar(v2);
        pai[raiz2] = raiz1;
    };

    vector<pair<int, int>> mst;
    int pesoTotal = 0;

    for (int i = 0; i < arestas.size(); i++)
    {
        int v1 = arestas[i].second.first;
        int v2 = arestas[i].second.second;
        int peso = arestas[i].first;

        if (encontrar(v1) != encontrar(v2))
        {
            unir(v1, v2);
            mst.push_back({v1, v2});
            pesoTotal += peso;
        }
    }

    cout << "Árvore Geradora Mínima (Kruskal):\n";
    for (int i = 0; i < mst.size(); i++)
    {
        cout << "Vértice " << mst[i].first << " -> Vértice " << mst[i].second << endl;
    }
    cout << "Peso total: " << pesoTotal << "\n";
}

void prim()
{
    vector<bool> visitado(numVertices, false);
    vector<int> menorPeso(numVertices, 99999);
    vector<int> pai(numVertices, -1);

    menorPeso[0] = 0;

    for (int i = 0; i < numVertices; i++)
    {
        int u = -1;
        for (int j = 0; j < numVertices; j++)
        {
            if (!visitado[j] && (u == -1 || menorPeso[j] < menorPeso[u]))
                u = j;
        }

        visitado[u] = true;

        for (int j = 0; j < adjacencias[u].size(); j++)
        {
            int v = adjacencias[u][j].vertice;
            int peso = adjacencias[u][j].peso;

            if (!visitado[v] && peso < menorPeso[v])
            {
                menorPeso[v] = peso;
                pai[v] = u;
            }
        }
    }

    cout << "Árvore Geradora Mínima (Prim):\n";
    int pesoTotal = 0;
    for (int i = 1; i < numVertices; i++)
    {
        if (pai[i] != -1)
        {
            cout << "Vértice " << pai[i] << " -> Vértice " << i << endl;
            pesoTotal += menorPeso[i];
        }
    }
    cout << "Peso total: " << pesoTotal << "\n";
}

void dijkstra(int origem, int destino)
{
    vector<int> distancia(numVertices, 99999);
    vector<int> pai(numVertices, -1);
    vector<bool> visitado(numVertices, false);

    distancia[origem] = 0;

    for (int i = 0; i < numVertices; i++)
    {
        int u = -1;
        for (int j = 0; j < numVertices; j++)
        {
            if (!visitado[j] && (u == -1 || distancia[j] < distancia[u]))
                u = j;
        }

        if (distancia[u] == 99999)
            break;

        visitado[u] = true;

        for (int j = 0; j < adjacencias[u].size(); j++)
        {
            int v = adjacencias[u][j].vertice;
            int peso = adjacencias[u][j].peso;

            if (distancia[u] + peso < distancia[v])
            {
                distancia[v] = distancia[u] + peso;
                pai[v] = u;
            }
        }
    }

    if (distancia[destino] == 99999)
    {
        cout << "Não existe caminho entre os vértices." << endl;
        return;
    }

    vector<int> caminho;
    for (int v = destino; v != -1; v = pai[v])
        caminho.push_back(v);

    cout << "Menor caminho (Dijkstra):\n";
    for (int i = caminho.size() - 1; i >= 0; i--)
    {
        cout << caminho[i];
        if (i > 0)
            cout << " -> ";
    }
    cout << "\nDistância total: " << distancia[destino] << "\n";
}

void exibirMenu()
{
    cout << "===== Menu Principal =====\n";
    cout << "1. Importar Grafo\n";
    cout << "2. Criar Grafo Vazio\n";
    cout << "3. Exibir Adjacências\n";
    cout << "4. Consultar Adjacência\n";
    cout << "5. Inserir Aresta\n";
    cout << "6. Árvore Geradora Mínima (Kruskal)\n";
    cout << "7. Árvore Geradora Mínima (Prim)\n";
    cout << "8. Menor Caminho (Dijkstra)\n";
    cout << "0. Sair\n\n";
    cout << "Escolha: ";
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int opcao;

    while (true)
    {
        system("cls");
        exibirMenu();
        cin >> opcao;

        if (opcao == 0)
            break;

        system("cls");
        switch (opcao)
        {
        case 1:
        {
            limparGrafo();
            char arquivo[256];
            cout << "Digite o nome do arquivo para importar o grafo: ";
            cin >> arquivo;
            importarGrafo(arquivo);
            break;
        }
        case 2:
        {
            limparGrafo();
            cout << "Digite o número de vértices do novo grafo: ";
            cin >> numVertices;
            coordenadas.resize(numVertices);
            adjacencias.resize(numVertices);
            nomesVertices.resize(numVertices);
            cout << "Novo grafo criado!\n";
            break;
        }
        case 3:
        {
            exibirAdjacencias();
            break;
        }
        case 4:
        {
            int v1, v2;
            cout << "Digite os vértices (v1 v2): ";
            cin >> v1 >> v2;
            bool adjacente = false;
            for (int i = 0; i < adjacencias[v1].size(); i++)
            {
                if (adjacencias[v1][i].vertice == v2)
                {
                    adjacente = true;
                    break;
                }
            }
            if (adjacente)
                cout << "Os vértices são adjacentes." << endl;
            else
                cout << "Os vértices não são adjacentes." << endl;
            break;
        }
        case 5:
        {
            int v1, v2, peso;
            cout << "Digite os vértices e o peso da aresta (v1 v2 peso): ";
            cin >> v1 >> v2 >> peso;
            inserirAresta(v1, v2, peso);
            cout << "Aresta inserida!\n";
            break;
        }
        case 6:
        {
            kruskal();
            break;
        }
        case 7:
        {
            prim();
            break;
        }
        case 8:
        {
            int origem, destino;
            cout << "Digite o número do vértice de origem: ";
            cin >> origem;
            cout << "Digite o número do vértice de destino: ";
            cin >> destino;

            if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices)
            {
                cout << "Vértice inválido!\n";
                break;
            }

            dijkstra(origem, destino);
            break;
        }
        default:
            cout << "Opção inválida!\n";
        }
        system("pause");
    }

    cout << "Programa encerrado.\n";
    return 0;
}
