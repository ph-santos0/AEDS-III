#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

struct Coordenada {
    int x;
    int y;
};

struct Aresta {
    int vertice;
    int peso;
};

bool direcionado;
int numVertices;
vector<Coordenada> coordenadas;
vector<vector<Aresta>> adjacencias;

void criarGrafo(bool dir, int vertices) {
    direcionado = dir;
    numVertices = vertices;
    adjacencias.resize(vertices);
}

void exibirAdjacencias() {
    cout << "===== Adjacências =====\n";
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vértice " << i << ":";
        if (!adjacencias[i].empty()) {
            for (const Aresta &aresta : adjacencias[i]) {
                cout << " -> " << aresta.vertice << " ";
            }
        } else {
            cout << " sem adjacências";
        }
        cout << endl;
    }
    cout << "========================\n";
}

bool consultarAdjacencia(int v1, int v2) {
    for (const Aresta &aresta : adjacencias[v1]) {
        if (aresta.vertice == v2) {
            return true;
        }
    }
    return false;
}

void inserirAresta(int v1, int v2, int peso) {
    adjacencias[v1].push_back({v2, peso});
    if (!direcionado) {
        adjacencias[v2].push_back({v1, peso});
    }
}

void removerAresta(int v1, int v2) {
    auto removeAdjacencia = [](int origem, int destino) {
        for (auto it = adjacencias[origem].begin(); it != adjacencias[origem].end(); ++it) {
            if (it->vertice == destino) {
                adjacencias[origem].erase(it);
                break;
            }
        }
    };
    removeAdjacencia(v1, v2);
    if (!direcionado) {
        removeAdjacencia(v2, v1);
    }
}

void editarCoordenada(int vertice, int x, int y) {
    if (vertice >= 0 && vertice < numVertices) {
        coordenadas[vertice] = {x, y};
        cout << "Coordenada do vértice " << vertice << " atualizada para (" << x << ", " << y << ").\n";
    } else {
        cout << "Vértice inválido!\n";
    }
}

void importarGrafo(const char *arquivo) {
    ifstream file(arquivo);
    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    string linha;
    getline(file, linha);
    direcionado = (linha.find("sim") != string::npos);

    file >> numVertices;
    coordenadas.resize(numVertices);
    adjacencias.resize(numVertices);

    for (int i = 0; i < numVertices; ++i) {
        int id, x, y;
        file >> id >> x >> y;
        coordenadas[id] = {x, y};
    }

    int numArestas;
    file >> numArestas;

    for (int i = 0; i < numArestas; ++i) {
        int v1, v2, peso;
        file >> v1 >> v2 >> peso;
        inserirAresta(v1, v2, peso);
    }

    file.close();
    cout << "Grafo importado com sucesso!\n";
}

void exportarGrafo(const char *arquivo) {
    ofstream file(arquivo);
    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    file << "direcionado=" << (direcionado ? "sim" : "nao") << endl;
    file << numVertices << endl;

    for (int i = 0; i < numVertices; ++i) {
        file << i << " " << coordenadas[i].x << " " << coordenadas[i].y << endl;
    }

    vector<pair<int, int>> arestasExportadas;
    int numArestas = 0;

    for (int i = 0; i < adjacencias.size(); ++i) {
        for (const Aresta &aresta : adjacencias[i]) {
            int v1 = i;
            int v2 = aresta.vertice;
            if (direcionado || v1 < v2) {
                arestasExportadas.push_back({v1, v2});
                numArestas++;
            }
        }
    }

    file << numArestas << endl;

    for (const auto &par : arestasExportadas) {
        int v1 = par.first;
        int v2 = par.second;
        for (const Aresta &aresta : adjacencias[v1]) {
            if (aresta.vertice == v2) {
                file << v1 << " " << v2 << " " << aresta.peso << endl;
                break;
            }
        }
    }

    file.close();
    cout << "Grafo exportado com sucesso!\n";
}

void exibirMenu() {
    cout << "===== Menu Principal =====\n";
    cout << "1. Importar Grafo\n";
    cout << "2. Criar Grafo Vazio\n";
    cout << "3. Exibir Adjacências\n";
    cout << "4. Consultar Adjacência\n";
    cout << "5. Inserir Aresta\n";
    cout << "6. Remover Aresta\n";
    cout << "7. Editar Coordenada\n";
    cout << "8. Exportar Grafo\n";
    cout << "0. Sair\n\n";
    cout << "Escolha: ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int opcao;

    while (true) {
        system("cls");
        exibirMenu();
        cin >> opcao;

        if (opcao == 0)
            break;

        system("cls");
        switch (opcao) {
        case 1: {
            char arquivo[256];
            cout << "Digite o nome do arquivo para importar o grafo: ";
            cin >> arquivo;
            importarGrafo(arquivo);
            break;
        }
        case 2: {
            int vertices;
            cout << "Digite o número de vértices: ";
            cin >> vertices;
            criarGrafo(false, vertices);
            cout << "Grafo vazio criado com " << vertices << " vértices.\n";
            break;
        }
        case 3:
            exibirAdjacencias();
            break;
        case 4: {
            int v1, v2;
            cout << "Digite os vértices para verificar adjacência (v1 v2): ";
            cin >> v1 >> v2;
            cout << (consultarAdjacencia(v1, v2) ? "São adjacentes" : "Não são adjacentes") << endl;
            break;
        }
        case 5: {
            int v1, v2, peso;
            cout << "Digite os vértices e o peso da aresta (v1 v2 peso): ";
            cin >> v1 >> v2 >> peso;
            inserirAresta(v1, v2, peso);
            cout << "Aresta inserida!\n";
            break;
        }
        case 6: {
            int v1, v2;
            cout << "Digite os vértices da aresta para remover (v1 v2): ";
            cin >> v1 >> v2;
            removerAresta(v1, v2);
            cout << "Aresta removida!\n";
            break;
        }
        case 7: {
            int vertice, x, y;
            cout << "Digite o vértice e as novas coordenadas (vértice x y): ";
            cin >> vertice >> x >> y;
            editarCoordenada(vertice, x, y);
            break;
        }
        case 8: {
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
