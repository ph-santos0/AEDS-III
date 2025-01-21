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
            for (const auto &aresta : adjacencias[i])
            {
                cout << " -> " << aresta.vertice;
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

void exibirMenu()
{
    cout << "===== Menu Principal =====\n";
    cout << "1. Importar Grafo\n";
    cout << "2. Criar Grafo Vazio\n";
    cout << "3. Exibir Adjacências\n";
    cout << "4. Consultar Adjacência\n";
    cout << "5. Inserir Aresta\n";
    cout << "16. Árvore geradora mínima (Kruskal)\n";
    cout << "17. Árvore geradora mínima (Prim)\n";
    cout << "18. Menor caminho (Dijkstra)\n";
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
        case 3:
            exibirAdjacencias();
            break;
        case 5:
        {
            int v1, v2, peso;
            cout << "Digite os vértices e o peso da aresta (v1 v2 peso): ";
            cin >> v1 >> v2 >> peso;
            inserirAresta(v1, v2, peso);
            cout << "Aresta inserida!\n";
            break;
        }
        case 16:
        {
            break;
        }
        case 17:
        {
            break;
        }
        case 18:
        {
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
