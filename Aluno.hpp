#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

namespace Aluno
{
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

} // namespace Aluno
