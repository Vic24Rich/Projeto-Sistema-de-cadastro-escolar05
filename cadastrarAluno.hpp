#include "Aluno.hpp"

void cadastrarAluno()
{
    Aluno::Aluno aluno;

    cout << "Digite a matricula do aluno: ";
    cin >> aluno.matricula;
    cin.ignore(80, '\n');

    cout << "Digite o nome de aluno: ";
    cin >> aluno.nome;

    cout << "Digite a media do aluno: ";
    cin >> aluno.media;
    cin.ignore(80, '\n');

    cout << "Digite a quantidade de falta do aluno: ";
    cin >> aluno.faltas;
    cin.ignore(80, '\n');

    Aluno::db_alunos.push_back(aluno);
}