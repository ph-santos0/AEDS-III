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

void limparGrafo()
{
    coordenadas.clear();
    adjacencias.clear();
}

void criarGrafo(bool dir, int vertices)
{
    direcionado = dir;
    numVertices = vertices;
    adjacencias.resize(vertices);
    coordenadas.resize(vertices);
}

void exibirAdjacencias()
{
    cout << "===== Adjacências =====\n";
    for (int i = 0; i < numVertices; i++)
    {
        cout << "Vértice " << i << ":";
        if (!adjacencias[i].empty())
        {
            for (int j = 0; j < adjacencias[i].size(); j++)
            {
                cout << " -> " << adjacencias[i][j].vertice << " ";
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

bool consultarAdjacencia(int v1, int v2)
{
    for (int i = 0; i < adjacencias[v1].size(); i++)
    {
        if (adjacencias[v1][i].vertice == v2)
        {
            return true;
        }
    }
    return false;
}

void inserirAresta(int v1, int v2, int peso)
{
    adjacencias[v1].push_back({v2, peso});
    if (!direcionado)
    {
        adjacencias[v2].push_back({v1, peso});
    }
}

void removerAresta(int v1, int v2)
{
    for (int i = 0; i < adjacencias[v1].size(); i++)
    {
        if (adjacencias[v1][i].vertice == v2)
        {
            adjacencias[v1].erase(adjacencias[v1].begin() + i);
            break;
        }
    }

    if (!direcionado)
    {
        for (int i = 0; i < adjacencias[v2].size(); i++)
        {
            if (adjacencias[v2][i].vertice == v1)
            {
                adjacencias[v2].erase(adjacencias[v2].begin() + i);
                break;
            }
        }
    }
}

void editarCoordenada(int vertice, int x, int y)
{
    if (vertice >= 0 && vertice < numVertices)
    {
        coordenadas[vertice] = {x, y};
        cout << "Coordenada do vértice " << vertice << " atualizada para (" << x << ", " << y << ").\n";
    }
    else
    {
        cout << "Vértice inválido!\n";
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

    for (int i = 0; i < numVertices; i++)
    {
        int id, x, y;
        file >> id >> x >> y;
        coordenadas[id] = {x, y};
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

void exportarGrafo(const char *arquivo)
{
    ofstream file(arquivo);
    if (!file.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    file << "direcionado=" << (direcionado ? "sim" : "nao") << endl;
    file << numVertices << endl;

    for (int i = 0; i < numVertices; i++)
    {
        file << i << " " << coordenadas[i].x << " " << coordenadas[i].y << endl;
    }

    vector<pair<int, int>> arestasExportadas;
    int numArestas = 0;

    for (int i = 0; i < adjacencias.size(); i++)
    {
        for (int j = 0; j < adjacencias[i].size(); j++)
        {
            int v1 = i;
            int v2 = adjacencias[i][j].vertice;
            if (direcionado || v1 < v2)
            {
                arestasExportadas.push_back({v1, v2});
                numArestas++;
            }
        }
    }

    file << numArestas << endl;

    for (int i = 0; i < arestasExportadas.size(); i++)
    {
        int v1 = arestasExportadas[i].first;
        int v2 = arestasExportadas[i].second;
        for (int j = 0; j < adjacencias[v1].size(); j++)
        {
            if (adjacencias[v1][j].vertice == v2)
            {
                file << v1 << " " << v2 << " " << adjacencias[v1][j].peso << endl;
                break;
            }
        }
    }

    file.close();
    cout << "Grafo exportado com sucesso!\n";
}

void consultarPrimeiroAdjacente(int vertice)
{
    if (!adjacencias[vertice].empty())
    {
        cout << "Primeiro adjacente do vértice " << vertice << ": " << adjacencias[vertice][0].vertice << endl;
    }
    else
    {
        cout << "O vértice " << vertice << " não possui adjacências.\n";
    }
}

void consultarProximoAdjacente(int vertice, int adjAtual)
{
    bool encontrado = false;
    for (int i = 0; i < adjacencias[vertice].size(); i++)
    {
        if (adjacencias[vertice][i].vertice == adjAtual && i + 1 < adjacencias[vertice].size())
        {
            cout << "Próximo adjacente após " << adjAtual << ": " << adjacencias[vertice][i + 1].vertice << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado)
    {
        cout << "Não há próximo adjacente para o vértice " << vertice << " após " << adjAtual << ".\n";
    }
}

void consultarListaAdjacentes(int vertice)
{
    if (!adjacencias[vertice].empty())
    {
        cout << "Lista de adjacentes do vértice " << vertice << ": ";
        for (int i = 0; i < adjacencias[vertice].size(); i++)
        {
            cout << adjacencias[vertice][i].vertice << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "O vértice " << vertice << " não possui adjacências.\n";
    }
}

void exibirMenu()
{
    cout << "===== Menu Principal =====\n";
    cout << "1. Importar Grafo\n";
    cout << "2. Criar Grafo Vazio\n";
    cout << "3. Exibir Adjacências\n";
    cout << "4. Consultar Adjacência\n";
    cout << "5. Inserir Aresta\n";
    cout << "6. Inserir arestas em conjunto\n";
    cout << "7. Remover Aresta\n";
    cout << "8. Editar Coordenada\n";
    cout << "9. Consultar Primeiro Adjacente\n";
    cout << "10. Consultar Próximo Adjacente\n";
    cout << "11. Consultar Lista Completa de Adjacentes\n";
    cout << "12. Exportar Grafo\n";
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
            int vertices;
            char escolha;

            cout << "O grafo será direcionado? (s/n): ";
            cin >> escolha;

            bool direcionado = (escolha == 's' || escolha == 'S');

            cout << "Digite o número de vértices: ";
            cin >> vertices;

            criarGrafo(direcionado, vertices);
            cout << "\nGrafo vazio" << (direcionado ? " direcionado " : " não direcionado ") << "criado com " << vertices << " vértices.\n";

            break;
        }

        case 3:
            exibirAdjacencias();
            break;
        case 4:
        {
            int v1, v2;
            cout << "Digite os vértices para verificar adjacência (v1 v2): ";
            cin >> v1 >> v2;
            cout << (consultarAdjacencia(v1, v2) ? "São adjacentes" : "Não são adjacentes") << endl;
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
            int v1, v2, peso, numfor;
            cout << "Digite o numero de arestas: ";
            cin >> numfor;

            for (int i = 0; i < numfor; i++)
            {
                cout << "Digite os vértices e o peso da aresta (v1 v2 peso): ";
                cin >> v1 >> v2 >> peso;

                adjacencias[v1].push_back({v2, peso});
                if (!direcionado)
                {
                    adjacencias[v2].push_back({v1, peso});
                }
            }

            cout << "Arestas inseridas!\n";
            break;
        }
        case 7:
        {
            int v1, v2;
            cout << "Digite os vértices da aresta para remover (v1 v2): ";
            cin >> v1 >> v2;
            removerAresta(v1, v2);
            cout << "Aresta removida!\n";
            break;
        }
        case 8:
        {
            int vertice, x, y;
            cout << "Digite o vértice e as novas coordenadas (vértice x y): ";
            cin >> vertice >> x >> y;
            editarCoordenada(vertice, x, y);
            break;
        }
        case 9:
        {
            int vertice;
            cout << "Digite o vértice: ";
            cin >> vertice;
            consultarPrimeiroAdjacente(vertice);
            break;
        }
        case 10:
        {
            int vertice, adjAtual;
            cout << "Digite o vértice e o adjacente atual (vértice adjAtual): ";
            cin >> vertice >> adjAtual;
            consultarProximoAdjacente(vertice, adjAtual);
            break;
        }
        case 11:
        {
            int vertice;
            cout << "Digite o vértice: ";
            cin >> vertice;
            consultarListaAdjacentes(vertice);
            break;
        }
        case 12:
        {
            char arquivo[256];
            cout << "Digite o nome do arquivo para exportar o grafo: ";
            cin >> arquivo;
            exportarGrafo(arquivo);
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
