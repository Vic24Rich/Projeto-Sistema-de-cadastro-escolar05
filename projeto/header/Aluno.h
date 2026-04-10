#ifndef ALUNO_H
#define ALUNO_H

#include <iostream>
#include <string>
#include <vector>
#include <winsock.h>

using namespace std;

struct Aluno
{
    u_int matricula;
    std::string nome;
    float media;
    u_int faltas;

    void dados()
    {
        cout << "Matricula: " << matricula <<
            "\nNome: " << nome <<
            "\nMedia: " << media <<
            "\nFaltas: " << faltas <<
            '\n';
    }
};

std::vector<Aluno> db_alunos;

#endif // ALUNO_H
