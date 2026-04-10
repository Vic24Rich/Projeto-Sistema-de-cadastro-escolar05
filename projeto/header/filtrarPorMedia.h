#ifndef FILTRARPORMEDIA_H
#define FILTRARPORMEDIA_H

#include <vector>
#include "Aluno.h"
#include "relatorioFaltas.h"
#include <algorithm>
#include <iomanip>

using namespace std;

// Implementação do Quick Sort para a ordenação das medias dos alunos do menor para o maior.
int divisao2(vector<Aluno> &aluno, int menor, int maior)
{
    int principal = aluno[maior].media;

    int i = (menor - 1);

    for (int j = menor; j <= maior - 1; j++)
    {
        if (aluno[j].media >= principal)
        {
            i++;
            swap(aluno[i], aluno[j]);
        }
    }

    swap(aluno[i + 1], aluno[maior]);
    return (i + 1);
}

void ordenarPorMedia(vector<Aluno> &aluno, int menor, int maior)
{
    if (menor < maior)
    {
        int faltaparte = divisao2(aluno, menor, maior);

        // Recursão para as duas metades
        ordenarPorMedia(aluno, menor, faltaparte - 1);
        ordenarPorMedia(aluno, faltaparte + 1, maior);
    }
}

void filtrarPorMedia(vector<Aluno> &alunos){

    if (alunos.empty()) {
        cout << "Nenhum aluno cadastrado.\n";
        return;
    }

    ordenarPorMedia(alunos, 0, alunos.size() - 1);

    cout << "\n========== RELATORIO DE MEDIA ==========\n";
    cout << left << setw(6)  << "ID"
         << setw(25) << "Nome"
         << setw(10) << "Media"
         << "Situacao\n";
    cout << "-------------------------------------------\n";

    for (const auto& aluno : alunos){
        // Exibe ID e Nome normalmente
        cout << left << setw(6)  << aluno.matricula
             << setw(25) << aluno.nome;

        bool reprovadoPorMedia = (aluno.media < 6);

        if (reprovadoPorMedia) {
            color(Black, Red);   // fundo preto, texto vermelho
            cout << setw(10) << aluno.faltas;
            color(Black, lgray); // volta à cor padrão (cinza claro)
        } else {
            color(Black, Green);
            cout << setw(10) << aluno.faltas;
            color(Black, lgray);
        }

        // Exibe situação
        if (reprovadoPorMedia) {
            color(Black, Red);
            cout << "Reprovado\n";
            color(Black, lgray);
        } else {
            color(Black, Green);
            cout << "Aprovado\n";
            color(Black, lgray);
        }
    }
}

#endif // FILTRARPORMEDIA_H
