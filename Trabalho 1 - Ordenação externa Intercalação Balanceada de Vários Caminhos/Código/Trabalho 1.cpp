#include <iostream>
#include <windows.h>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

void criarFitas();
void abrirFitas();
void externalSort();
int compare(const void* a, const void* b);
int comparePair(const void* a, const void* b);
void montarBlocosIniciais(const string& dados);
void intercalacar();
void gerarSaida(int fitaFinal);
void fecharFitas();

ifstream* fitasLeitura;
ofstream* fitasGravacao;

bool lendoMetadeCima;

char separador = '*';

int quantidadeFitas;
int tamanhoMemoria;

void criarFitas() {
    ofstream saida;
    for(int i = 0; i < quantidadeFitas; i++) {
        saida.open("./fita" + to_string(i) + ".txt");
        saida.close();
    }
}

void abrirFitas() {
    int comecoGravacao, fimGravacao;
    int comecoLeitura, fimLeitura;

    if(lendoMetadeCima) {
        comecoLeitura = 0;
        fimLeitura = quantidadeFitas / 2;

        comecoGravacao = quantidadeFitas / 2;
        fimGravacao = quantidadeFitas;
    } else {
        comecoGravacao = 0;
        fimGravacao = quantidadeFitas / 2;

        comecoLeitura = quantidadeFitas / 2;
        fimLeitura = quantidadeFitas;
    }  
    
    fitasGravacao = new ofstream[quantidadeFitas / 2];
    fitasLeitura = new ifstream[quantidadeFitas / 2];

    int auxCont = 0;
    for(int i = comecoGravacao; i < fimGravacao; i++) {
        fitasGravacao[auxCont].open("fita" + to_string(i) + ".txt", fstream::out);
        auxCont++;
    }

    auxCont = 0;
    for(int i = comecoLeitura; i < fimLeitura; i++) {
        fitasLeitura[auxCont].open("fita" + to_string(i) + ".txt", fstream::in);
        auxCont++;
    }
}

void ordenacaoExterna() {
    ifstream entrada("entrada.txt");
    if (!entrada) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return;
    }
    
    entrada >> tamanhoMemoria >> quantidadeFitas;
    string dados;
    entrada.ignore();
    getline(entrada, dados);
    entrada.close();

    lendoMetadeCima = false;
    criarFitas();
    montarBlocosIniciais(dados);
    intercalacar();
}

int compare(const void* a, const void* b) {
    const char* x = (char*) a;
    const char* y = (char*) b;

    if(*x > *y) {
        return 1;
    } else if(*x < *y) {
        return -1;
    }
    return 0;
}

int comparePair(const void* a, const void* b) {
    const pair<char, int>* x = (pair<char, int>*) a;
    const pair<char, int>* y = (pair<char, int>*) b;

    if((*x).first > (*y).first) {
        return 1;
    } else if((*x).first < (*y).first) {
        return -1;
    }
    return 0;
}

void montarBlocosIniciais(const string& dados) {
    char memoria[tamanhoMemoria];
    int auxCont = 0;
    abrirFitas();

    for(size_t i = 0; i < dados.size(); i += tamanhoMemoria) {
        size_t tamanhoVetor = min(tamanhoMemoria, static_cast<int>(dados.size() - i));
        strncpy(memoria, dados.c_str() + i, tamanhoVetor);

        qsort(memoria, tamanhoVetor, sizeof(char), compare);

        if(auxCont >= quantidadeFitas / 2) {
            auxCont = 0;
        }

        fitasGravacao[auxCont] << string(memoria, tamanhoVetor) << separador;
        auxCont++;
    }
    lendoMetadeCima = !lendoMetadeCima;
    fecharFitas();
}

void intercalacar() {
    pair<char, int> memoria[tamanhoMemoria];

    bool fitaAberta[quantidadeFitas / 2];
    bool fitaVazia[quantidadeFitas / 2];
    bool intercalando = true;
    bool passosRestando = true;
    bool intercalacoesRestantes = true;
    bool foiGravada[quantidadeFitas / 2];

    int fitasVazias = 0;
    int contMemoria = 0;
    int contGravacao = 0;
    int contFitas = 0;
    int fitasDisponiveis = quantidadeFitas / 2;
    int fitasGravadas = quantidadeFitas / 2;
    
    int fitaFinal;

    char charAux = '\0';

    while(intercalacoesRestantes) {
        
        abrirFitas();

        contGravacao = 0;
        fitasVazias = 0;
        intercalando = true;

        for(int i = 0; i < quantidadeFitas / 2; i++) {
            if(fitasLeitura[i].peek() == EOF) {
                fitaVazia[i] = true;
                fitasVazias++;
            } else {
                fitaVazia[i] = false;
            }
            foiGravada[i] = false;
        }

        while(intercalando) {
            for(int i = 0; i < quantidadeFitas / 2; i++) {
                fitaAberta[i] = true;
            }

            fitasDisponiveis = (quantidadeFitas / 2) - fitasVazias;
            contFitas = 0;
            contMemoria = 0;
            charAux = '\0';    
            passosRestando = true;   

            while(passosRestando) {            
                if(fitaAberta[contFitas] && !fitaVazia[contFitas]) {

                    fitasLeitura[contFitas].get(charAux);
                
                    if(charAux == separador) {     
                        if(fitasLeitura[contFitas].peek() == EOF) {
                            fitaVazia[contFitas] = true;                       
                            fitasVazias++;
                        }              
                        fitaAberta[contFitas] = false;
                        fitasDisponiveis--;
                    } else {
                        memoria[contMemoria].first = charAux;                    
                        memoria[contMemoria].second = contFitas;
                        contMemoria++;                    
                    }
                }
                
                contFitas++;
                if(contFitas == quantidadeFitas / 2) {
                    contFitas = 0;
                }

                if(contMemoria == tamanhoMemoria || fitasDisponiveis == 0) {
                    if(contMemoria != 1) {
                        qsort(memoria, contMemoria, sizeof(pair<char, int>), comparePair);
                    }
                    pair<char, int> aux = memoria[0];
                    memoria[0] = memoria[contMemoria-1];
                    memoria[contMemoria-1] = aux;

                    fitasGravacao[contGravacao] << aux.first;
                    contFitas = aux.second;
                    contMemoria--;
                }

                if((fitasDisponiveis == 0 && contMemoria == 0)) {
                    passosRestando = false;
                }
            }

            fitasGravacao[contGravacao] << separador;
            foiGravada[contGravacao] = true;
            contGravacao++;

            if(contGravacao == quantidadeFitas / 2) {
                contGravacao = 0;
            }
            if(fitasVazias == quantidadeFitas / 2) {
                intercalando = false;
            }        
        }
       
        fitasGravadas = 0;
        for(int i = 0; i < quantidadeFitas / 2; i++) {
            if(foiGravada[i]) {
                fitasGravadas++;
                fitaFinal = i;
            }
        }        
        fecharFitas();
        if(fitasGravadas == 1) {
            intercalacoesRestantes = false;
            gerarSaida(fitaFinal);
        }
        lendoMetadeCima = !lendoMetadeCima;
    }
}

void fecharFitas() {
    for(int i = 0; i < quantidadeFitas / 2; i++) {
        fitasGravacao[i].close();
        fitasLeitura[i].close();
    }
    delete[] fitasLeitura;
    delete[] fitasGravacao;
}

void gerarSaida(int fitaFinal) {
    if(lendoMetadeCima) {
        fitaFinal += quantidadeFitas / 2;
    }
    string aux = "fita" + to_string(fitaFinal) + ".txt";
    const char* saida = aux.c_str();

    remove("Saida.txt");
    rename(saida, "Saida.txt");
}

int main() {

    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    ordenacaoExterna();
    cout << "Ordenação concluída. O resultado está em 'Saida.txt'." << endl;
    return 0;
}
