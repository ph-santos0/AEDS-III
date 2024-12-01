#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

struct Item {
    int id;
};

void troca(Item& pai, Item& filho) {
    Item aux = pai;
    pai = filho;
    filho = aux;
}

void refaz(vector<Item>& vetor, int pai, int tamanho) {
    int filho = 2 * pai + 1;
    while (filho < tamanho) {
        if (filho + 1 < tamanho && vetor[filho].id < vetor[filho + 1].id) {
            filho++;
        }
        if (vetor[pai].id >= vetor[filho].id) {
            break;
        }
        troca(vetor[pai], vetor[filho]);
        pai = filho;
        filho = 2 * pai + 1;
    }
}

void heapsort(vector<Item>& vetor) {
    int tamanho = vetor.size();
    
    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        refaz(vetor, i, tamanho);
    }
    
    for (int i = tamanho - 1; i > 0; i--) {
        troca(vetor[0], vetor[i]);
        refaz(vetor, 0, i);
    }
}

int main() {
    SetConsoleOutputCP(65001);

    vector<Item> vetor = {{5}, {3}, {8}, {1}, {2}, {7}, {6}, {4}};
    
    cout << "Vetor original: ";
    for (const auto& item : vetor) {
        cout << item.id << " ";
    }
    cout << endl;

    heapsort(vetor);

    cout << "Vetor ordenado: ";
    for (const auto& item : vetor) {
        cout << item.id << " ";
    }
    cout << endl;

    return 0;
}
