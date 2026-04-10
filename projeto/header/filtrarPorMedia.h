#ifndef FILTRARPORMEDIA_H
#define FILTRARPORMEDIA_H

#include <vector>
#include "Aluno.h"
#include <algorithm>

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

void filtrarPorMedia(vector<Aluno> &aluno, int menor, int maior)
{
    if (menor < maior)
    {
        int faltaparte = divisao2(aluno, menor, maior);

        // Recursão para as duas metades
        filtrarPorMedia(aluno, menor, faltaparte - 1);
        filtrarPorMedia(aluno, faltaparte + 1, maior);
    }
}

#endif // FILTRARPORMEDIA_H
