#ifndef RELATORIOFALTAS_H
#define RELATORIOFALTAS_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <cstdint>
#include "Aluno.h"

using namespace std;

#define Black     0 // Preto
#define Green     2 // Verde
#define Red       4 // Vermelho
#define lgray     7 // Cinza Claro
const int TOTAL_AULAS = 100;

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

//QuickSort decrescente para ordenar por faltas
int partitionFDec(vector<Aluno>& alunos, int low, int high) {
    // Escolha de pivô aleatório para evitar pior caso O(n²)
    int randomIndex = low + rand() % (high - low + 1);
    swap(alunos[randomIndex], alunos[high]);
    int pivot = alunos[high].faltas;  // pivô baseado no número de faltas
    int i = low - 1;

    // Para ordem decrescente: elementos com faltas MAIORES ou IGUAIS ao pivô vão para a esquerda
    for (int j = low; j <= high - 1; j++) {
        if (alunos[j].faltas >= pivot) {
            i++;
            swap(alunos[i], alunos[j]);
        }
    }
    swap(alunos[i + 1], alunos[high]);
    return (i + 1);
}

// QuickSort decrescente por faltas
void quickSortFDec(vector<Aluno>& alunos, int low, int high) {
    if (low < high) {
        int part = partitionFDec(alunos, low, high);
        quickSortFDec(alunos, low, part - 1);
        quickSortFDec(alunos, part + 1, high);
    }
}

// tabela de faltas ordenada por quantidade de faltas
// irei reaproveitar a função quickSort para ordenar os alunos

// implementando a variavel totalAulas pois não sei se o numero de aulas é fixo
void filtrarPorFalta(vector<Aluno>& alunos) {
    int totalAulas = TOTAL_AULAS;

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
        cout << left << setw(6)  << aluno.matricula
             << setw(25) << aluno.nome;

        // Verifica se estourou o limite de faltas
        bool reprovadoPorFaltas = (aluno.faltas > limiteFaltas);

        // Exibe faltas (em vermelho se reprovado)
        if (reprovadoPorFaltas) {
            color(Black, Red);   // fundo preto, texto vermelho
            cout << setw(10) << aluno.faltas;
            color(Black, lgray); // volta à cor padrão (cinza claro)
        } else {
            color(Black, Green);
            cout << setw(10) << aluno.faltas;
            color(Black, lgray);
        }

        // Exibe situação
        if (reprovadoPorFaltas) {
            color(Black, Red);   // fundo preto, texto vermelho
            cout << "Reprovado por faltas\n";
            color(Black, lgray);
        } else {
            cout << "Cursando\n";
        }
    }
    cout << "===========================================\n";
}

#endif // RELATORIOFALTAS_H
