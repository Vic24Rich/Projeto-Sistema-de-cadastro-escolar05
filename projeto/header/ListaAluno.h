#ifndef LISTAALUNO_H
#define LISTAALUNO_H

#include "Aluno.h"

void enterPContinuar()
{
    cout << "<ENTER> para continuar... ";
    cin.get();
    system("cls");
}

void listarAlunos(vector<Aluno> db_alunos)
{
    system("cls");
    cout << "======== Alunos Cadastrados ========" << '\n' << '\n';
    for (Aluno aluno : db_alunos)
    {
        aluno.dados();
        cout << '\n';
    }
    cout << "====================================" << '\n' << '\n';
    enterPContinuar();
}

#endif // LISTAALUNO_H
