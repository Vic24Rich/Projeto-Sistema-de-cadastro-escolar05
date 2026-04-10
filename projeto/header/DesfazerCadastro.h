#ifndef DESFAZERCADASTRO_H
#define DESFAZERCADASTRO_H

#include "Aluno.h"

void desfazerCadastro(vector<Aluno> &db_alunos)
{
    int tamanho = db_alunos.size();
    vector<Aluno> aux;
    for (size_t i = tamanho; i > 0; i--)
    {
        aux.push_back(db_alunos[i - 1]);
        cout << i - 1;
    }

    aux.pop_back();
    cout << '\n';

    for (size_t i = 0; i < tamanho; i++)
    {
        db_alunos.pop_back();
        cout << i;
    }

    tamanho = aux.size();

    for (size_t i = tamanho; i > 0; i--)
    {
        db_alunos.push_back(aux[i - 1]);
    }

}

#endif // DESFAZERCADASTRO_H
