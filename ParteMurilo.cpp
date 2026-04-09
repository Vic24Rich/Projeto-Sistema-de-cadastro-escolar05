// minha parte do codigo: Murilo Juttel
// Sistema de faltas dos alunos:
// - Criação de tabela ordenada por faltas
// - coloração vermelha para alunos com mais de 25% de faltas
// busca de alunos:
// - busca binaria por matricula do aluno

#include <iomanip>
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <cstdint>

using namespace std;

#define Black     0 // Preto
#define Green     2 // Verde
#define Red       4 // Vermelho
#define lgray     7 // Cinza Claro
const int TOTAL_AULAS = 100;

struct CadAluno {
    int id;
    string Nome;
    array<float, 4> Notas;
    float Media;
    int Faltas;
    string situacao = "cursando";
};

void color(int corFundo, int corTexto) {
    HANDLE tela;
    int16_t cor;
    tela = GetStdHandle(STD_OUTPUT_HANDLE);
    if (corFundo < 0 || corFundo > 15 || corTexto < 0 ||
        corTexto > 15)
        cor = 15;
    else
        cor = corTexto + corFundo * 16;
    SetConsoleTextAttribute(tela, cor);
}

// para fazer a busca binaria, os alunos precisam estar ordenados por id
// irei usar o QuickSort para ordenar os alunos que usa um pivot para dividir o vetor
// em partes menores e ordenar cada parte recursivamente

int partition(vector<CadAluno>& alunos, int low, int high){
    // a escolha de um pivot aleatorio veio de um conselho de um professor
    // ele serve para evitar que no pior caso ele tenha tempo de O(n²) e passe a ter
    // um tempo constante de O(n log n)
    int randomIndex = low + rand() % (high - low + 1);
    swap(alunos[randomIndex], alunos[high]);
    int pivot = alunos[high].id;
    int i = low - 1;

    for(int j = low; j <= high - 1; j++){
        if (alunos[j].id <= pivot){
            i++;
            swap(alunos[i], alunos[j]);
        }
    }
    swap(alunos[i + 1], alunos[high]);
    return (i + 1);
}

void quickSort(vector<CadAluno>& alunos, int low, int high){
    if (low < high){
        int pivot = partition(alunos, low, high);

        quickSort(alunos, low, pivot - 1);
        quickSort(alunos, pivot + 1, high);
    }
}

//QuickSort decrescente para ordenar por faltas
int partitionFDec(vector<CadAluno>& alunos, int low, int high) {
    // Escolha de pivô aleatório para evitar pior caso O(n²)
    int randomIndex = low + rand() % (high - low + 1);
    swap(alunos[randomIndex], alunos[high]);
    int pivot = alunos[high].Faltas;  // pivô baseado no número de faltas
    int i = low - 1;

    // Para ordem decrescente: elementos com faltas MAIORES ou IGUAIS ao pivô vão para a esquerda
    for (int j = low; j <= high - 1; j++) {
        if (alunos[j].Faltas >= pivot) {
            i++;
            swap(alunos[i], alunos[j]);
        }
    }
    swap(alunos[i + 1], alunos[high]);
    return (i + 1);
}

// QuickSort decrescente por faltas
void quickSortFDec(vector<CadAluno>& alunos, int low, int high) {
    if (low < high) {
        int part = partitionFDec(alunos, low, high);
        quickSortFDec(alunos, low, part - 1);
        quickSortFDec(alunos, part + 1, high);
    }
}


// para a busca por matricula, foi pedido o uso de busca binaria

int buscaAluno(vector<CadAluno>& alunos, int id){
    int low = 0;
    int high = alunos.size() - 1;

    quickSort(alunos, low, high); // chamada do quicksort para ordenar

    do{
        int mid = low + (high - low) / 2;

        if(alunos[mid].id == id)
            return mid;
        else if (alunos[mid].id < id)
            low = mid + 1;
        else
            high = mid - 1;
    } while (low <= high);
    return -1; // se não for encontrado returna -1, PRECISA SER TRATADO NA MAIN
}

// tabela de faltas ordenada por quantidade de faltas
// irei reaproveitar a função quickSort para ordenar os alunos

// implementando a variavel totalAulas pois não sei se o numero de aulas é fixo
// PODE HAVER ALTERAÇÕES

void faltaAlunos(vector<CadAluno>& alunos, int totalAulas = TOTAL_AULAS) {
    // verifica se esta vazio
    if (alunos.empty()) {
        cout << "Nenhum aluno cadastrado.\n";
        return;
    }

    // Ordenar a lista em ordem decrescente de faltas
    quickSortFDec(alunos, 0, alunos.size() - 1);

    // Exibir cabeçalho do relatório
    cout << "\n========== RELATORIO DE FALTAS ==========\n";
    cout << left << setw(6)  << "ID"
         << setw(25) << "Nome"
         << setw(10) << "Faltas"
         << "Situacao\n";
    cout << "-------------------------------------------\n";

    // Percorrer a lista já ordenada
    double limiteFaltas = 0.25 * totalAulas;

    for (const auto& aluno : alunos) {
        // Exibe ID e Nome normalmente
        cout << left << setw(6)  << aluno.id
             << setw(25) << aluno.Nome;

        // Verifica se estourou o limite de faltas
        bool reprovadoPorFaltas = (aluno.Faltas > limiteFaltas);

        // Exibe faltas (em vermelho se reprovado)
        if (reprovadoPorFaltas) {
            color(Black, Red);   // fundo preto, texto vermelho
            cout << setw(10) << aluno.Faltas;
            color(Black, lgray); // volta à cor padrão (cinza claro)
        } else {
            color(Black, Green);
            cout << setw(10) << aluno.Faltas;
            color(Black, lgray);
        }

        // Exibe situação
        if (reprovadoPorFaltas) {
            cout << "Reprovado por faltas\n";
        } else {
            cout << aluno.situacao << "\n";
        }
    }
    cout << "===========================================\n";
}


// void faltaAlunos(vector<CadAluno> &alunos, int totalAulas) {
//     for (auto &aluno : alunos) {
//         float porcentagemFaltas =
//             (static_cast<float>(aluno.Faltas) / totalAulas) * 100;

//         if (porcentagemFaltas > 25.0f)
//             aluno.situacao = "Reprovado por faltas";
//         else
//             aluno.situacao = "Dentro do limite";
//     }

//     quickSort(alunos, 0, alunos.size() - 1);

//     // laçõ de exibição
//     for (const auto &aluno : alunos) {
//         cout << "ID: " << aluno.id << ", Nome: " << aluno.Nome;
//         if (aluno.situacao == "Reprovado por faltas")
//             color(4, 0); // letra vermelho fundo preto
//         else
//             color(2, 0); // letra verde fundo preto
//         cout << ", Faltas: " << aluno.Faltas << ", Situação: " << aluno.situacao
//              << endl;
//         color(0, 7); // padrão
//     }
// }